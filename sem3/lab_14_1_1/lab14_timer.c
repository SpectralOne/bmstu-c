#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ui.h"

#include "lab10_src/custom_defines.h"
#include "lab10_src/custom_errors.h"
#include "lab10_src/io_funcs.h"
#include "lab10_src/memmory_funcs.h"
#include "lab10_src/sort.h"
#include "lab10_src/utility_funcs.h"
#include "lab10_src/err_handler.h"

// Не известно, когда завершится программа
// А память ресурсы нужно освободить
void __attribute__((destructor)) destroy_array(void);

// Поле вывода
uiMultilineEntry *result;

// Поля ввода
uiEntry *surname, *date, *sex, *grades;

// Статус-метка
uiLabel *status_label;

// Переменные, относящиеся к радио-группе
static int rb_data = 0, rb_changed = 0;

// Флаг окончания сортировки
static int all_sorted = 0;

// Переменные к главному массиву
static int cur_pos = 0, main_array_size = 0;
person_s **main_arr = NULL;

/**
 * @brief Событие сброса текста для статус-метки
 * 
 */
static int resetLabel(void *data)
{
    uiLabelSetText(status_label ,"Status label (waiting)");
    return 1;
}

/**
 * @brief Функция сброса сортировки. Убирает флаг, обнуляет стартовую позицию
 * 
 */
void reset_sort(void)
{
    cur_pos = 0;
    all_sorted = 0;
}

/**
 * @brief Функция вывода сообщения об ошибке в статус-метку
 * 
 * @param error - Сообщение об ошибке
 */
void handle_status(const char *error)
{
    uiLabelSetText(status_label, error);
}

/**
 * @brief Системная функция освобождения ресурсов
 * 
 */
static int onClosing(uiWindow *w, void *data)
{
	uiQuit();
	return 1;
}

/**
 * @brief Системная функция освобождения ресурсов
 * 
 */
static int onShouldQuit(void *data)
{
	uiWindow *mainwin = uiWindow(data);

	uiControlDestroy(uiControl(mainwin));
	return 1;
}

/**
 * @brief Функция печати массива структур в Entry поле result
 * 
 * @param arr - Указатель на массив размер
 * @param size - Pазмер
 */
static void to_entry(person_s **arr, const int size)
{
    char grades_buf[GRADES_BUF_LEN + 1], line_buf[LINE_BUF_LEN + 1];
    uiMultilineEntrySetText(result, "");
    for (int i = 0; i < size; i++)
    {
        snprintf(line_buf, sizeof(line_buf), "%2d | %20s | %7s | %12s | ", i + 1, arr[i]->surname, arr[i]->sex, arr[i]->birth_day);
        uiMultilineEntryAppend(result, line_buf);

        for (int j = 0; j < arr[i]->grades->count; j++)
        {
            sprintf(grades_buf, "%d ", arr[i]->grades->grades_array[j]);
            uiMultilineEntryAppend(result, grades_buf);
        }
        uiMultilineEntryAppend(result, "\n");
    }
}

/**
 * @brief Функция проверяет, если переданная структура в массиве уже есть
 * 
 * @param new_record - Указатель на структуру
 */
int duplicate_check(person_s *new_record)
{
    if (!main_arr)
        return puts("NULL"), OK;
    
    for (int i = 0; i < main_array_size; i++)
        if (find_in_arr(main_arr, main_array_size, new_record))
            return OK;
    return OK;
}

/**
 * @brief Функция дописывает в конец массива переданную структуру
 * 
 * @param new_record - Указатель на структуру
 */
int append_array(person_s *new_record)
{
    person_s **tmp = NULL;
    int status = OK;
    tmp = reallocate_struct_array(main_arr, &status, main_array_size + 1);
    if (tmp)
    {
        main_arr = tmp;
        main_arr[main_array_size] = new_record;
        main_array_size++;
    }
    return status;
}

/**
 * @brief Обработчик нажатия кнопки 'Add 3 to grades'
 */
static void onAddGradesClicked(uiButton *b, void *data)
{
    if (!main_array_size)
        return handle_status("Empty array");
    
    int status = add_three_all(main_arr, main_array_size);
    if (status == OK)
        reset_sort();
    handle_status(err_handler(status));
}

/**
 * @brief Обработчик нажатия кнопки 'Add'
 */
static void onAddClicked(uiButton *b, void *data)
{
    int status = OK;

    status = check_string(uiEntryText(surname));
    if (status == OK)
    {   
        status = check_sex_string(uiEntryText(sex));
        if (status > 0)
        {
            status = check_date_string(uiEntryText(date), DATE_FORMAT);
            if (status == VALID)
            {
                status = check_grades(uiEntryText(grades));
                if (status == OK)
                {
                    person_s *new_record = allocate_struct(&status);
                    if (new_record && status == OK)
                    {
                        status = fill_record(new_record, uiEntryText(surname), uiEntryText(sex), uiEntryText(date), uiEntryText(grades));
                        if (status == OK)
                        {
                            status = duplicate_check(new_record);
                            if (status == OK)
                            {
                                status = append_array(new_record);
                                if (status == OK)
                                    reset_sort();
                            }
                        }   
                        if (status != OK)
                            free_struct(new_record);
                    }
                }
            }
        }
    }

    handle_status(err_handler(status));
}

/**
 * @brief Обработчик нажатия кнопки 'Remove age > 17'
 */
static void onTaskClicked(uiButton *b, void *data)
{
    if (!main_array_size)
        return handle_status("Empty array");
    
    person_s **tmp = main_arr;
    int tmp_size = main_array_size;
    if (normalize_array(&tmp, &tmp_size, DELETE_FORMAT) == OK)
    {
            main_arr = tmp;
            main_array_size = tmp_size;
            reset_sort();
            return handle_status("Done!");
    }
    else
        handle_status("Empty array or Internar error");
}

/**
 * @brief Частичная сортировка. Событие для таймера.
 */
static int partSort(void *data)
{
    if (main_arr)
    {    
        if (rb_changed)
        {
            reset_sort();
            rb_changed = 0;
        }

        if (cur_pos == main_array_size)
        {
            cur_pos = 0; 
            all_sorted = 1;
        }

        if (all_sorted)
            return 1;

        if (main_array_size)
        {   
            switch (rb_data)
            {
            case 1:
                partial_sort(main_arr, main_array_size, &compare_sex, cur_pos);
                break;
            case 2:
                partial_sort(main_arr, main_array_size, &compare_birth_date, cur_pos);
                break;
            case 3:
                partial_sort(main_arr, main_array_size, &compare_grade_average, cur_pos);
                break;
            default:
                partial_sort(main_arr, main_array_size, &compare_surname, cur_pos);
                break;
            }
            to_entry(main_arr, main_array_size);
            cur_pos++;
        }
    }

    return 1;
}

/**
 * @brief Обработчик события переключения кнопок радио-группы
 */
void onSet(uiRadioButtons *rb, void *data)
{
    rb_data = uiRadioButtonsSelected(rb);
    rb_changed = 1;
}

/**
 * @brief Функция создания главной формы
 * 
 * @return uiControl - Указатель на созданную форму 
 */
static uiControl *makeMainPage(void)
{
	uiBox *vbox;
	uiBox *hbox;
	uiGroup *group;
	uiForm *entryForm, *dataForm, *sortForm;
    uiRadioButtons *rb;
    uiButton *b;

	vbox = uiNewVerticalBox();
	uiBoxSetPadded(vbox, 1);

	hbox = uiNewHorizontalBox();
	uiBoxSetPadded(hbox, 1);
	uiBoxAppend(vbox, uiControl(hbox), 0);
    
    // Input data -- group
    group = uiNewGroup("Input data");
	uiGroupSetMargined(group, 1);
    uiBoxAppend(hbox, uiControl(group), 1);
	
    // Input data -- form
    dataForm = uiNewForm();
	uiFormSetPadded(dataForm, 1);
	uiGroupSetChild(group, uiControl(dataForm));
    
    surname = uiNewEntry();
    sex = uiNewEntry();
    grades = uiNewEntry();
    date = uiNewEntry();

    uiFormAppend(dataForm, "Surname", uiControl(surname), 1);
    uiFormAppend(dataForm, "Sex", uiControl(sex), 1);
    uiFormAppend(dataForm, "Bday", uiControl(date), 1);
    uiFormAppend(dataForm, "grades", uiControl(grades), 1);

    b = uiNewButton("Add");
    uiButtonOnClicked(b, onAddClicked, NULL);
	uiFormAppend(dataForm, "--->", uiControl(b), 1);
    
    // Sort options -- group
    group = uiNewGroup("Sort options");
    uiGroupSetMargined(group, 1);
    uiBoxAppend(hbox, uiControl(group), 1);

    // Sort options -- form
    sortForm = uiNewForm();
	uiFormSetPadded(sortForm, 1);
	uiGroupSetChild(group, uiControl(sortForm));

    uiFormAppend(sortForm, NULL, uiControl(uiNewLabel("Select field")), 0);

    rb = uiNewRadioButtons();
	uiRadioButtonsAppend(rb, "Surname");
	uiRadioButtonsAppend(rb, "Sex");
    uiRadioButtonsAppend(rb, "Bday");
	uiRadioButtonsAppend(rb, "Grades");
    uiRadioButtonsOnSelected(rb, onSet, NULL);
	uiFormAppend(sortForm, NULL, uiControl(rb), 1);

    uiFormAppend(sortForm, NULL, uiControl(uiNewLabel("Misc")), 0);
    
    b = uiNewButton("Remove age > 17");
    uiButtonOnClicked(b, onTaskClicked, NULL);
	uiFormAppend(sortForm, NULL, uiControl(b), 0);

    b = uiNewButton("Add 3 to grades");
    uiButtonOnClicked(b, onAddGradesClicked, NULL);
	uiFormAppend(sortForm, NULL, uiControl(b), 0);

    status_label = uiNewLabel("Status label (errors)");
    uiFormAppend(sortForm, "--->", uiControl(status_label), 0);

	uiBoxAppend(vbox, uiControl(uiNewHorizontalSeparator()), 0);

    // Kid's table -- group
	group = uiNewGroup("Kid's table");
	uiGroupSetMargined(group, 1);
	uiBoxAppend(vbox, uiControl(group), 1);

    // Kid's table -- form
	entryForm = uiNewForm();
	uiFormSetPadded(entryForm, 1);
	uiGroupSetChild(group, uiControl(entryForm));

    result = uiNewMultilineEntry();
    uiMultilineEntrySetReadOnly(result, 1);
    uiMultilineEntrySetText(result, "No output");

    uiFormAppend(entryForm, NULL, uiControl(result), 1);

	return uiControl(vbox);
}

int main(void)
{
    uiWindow *mainwin;
	uiInitOptions options;
	const char *err;
	uiTab *tab;

	memset(&options, 0, sizeof (uiInitOptions));
	err = uiInit(&options);
	if (err != NULL) {
		fprintf(stderr, "error initializing libui: %s", err);
		uiFreeInitError(err);
		return 1;
	}

	mainwin = uiNewWindow("Lab 10 graphic interface", 640, 480, 1);
	uiWindowOnClosing(mainwin, onClosing, NULL);
	uiOnShouldQuit(onShouldQuit, mainwin);

	uiWindowSetChild(mainwin, uiControl(makeMainPage()));
	uiWindowSetMargined(mainwin, 1);

    // Timer events
    uiTimer(2000, partSort, NULL);
    uiTimer(8000, resetLabel, NULL);
    
    uiControlShow(uiControl(mainwin));
	uiMain();
	
    return OK;
}

/**
 * @brief Освобождение выделенной памяти при выходе из программы
 */
void destroy_array(void)
{
    if (main_arr)
        free_struct_array(main_arr, main_array_size);
}