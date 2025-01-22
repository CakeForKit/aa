#include "queue.h"

pthread_mutex_t mutex_q2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_q3 = PTHREAD_MUTEX_INITIALIZER;
queue_t q1 = {NULL, NULL};
queue_t q2 = {NULL, NULL};
queue_t q3 = {NULL, NULL};
group_t groups[N];


void print_groups() {
    for (size_t i = 0; i < N; ++i) {
        printf("gr %ld: sum=%d, len=%ld: ", i, groups[i].sum, 
                                            groups[i].len_pars);
        for (size_t j = 0; j < groups[i].len_pars; ++j) {
            printf("%d ", groups[i].pairs[j]->num);
        }
        printf("\n");
    }
}

/*  ОУ1: 
    read_str from file 
    создать на ее основе struct pair
    положить struct pair в очередь Q2   */
void *read_pair(void *arg) {
    (void) arg;

    char *filename;
    assert(get(&q1, (void *) &filename) == 0);
    FILE *f = fopen(filename, "r");
    assert(f != NULL);

    char key[MAX_LEN_KEY];
    int num;
    while (fscanf(f, "%s : %d\n", &(key[0]), &num) != EOF) {
        pair_t *pair = malloc(sizeof(pair_t));
        assert(pair != NULL);
        strcpy(pair->key, key);
        pair->num = num;

        pthread_mutex_lock(&mutex_q2);
        // printf("put pair = %s : %d\n", pair->key, pair->num);
        assert(put(&q2, pair) == 0);
        pthread_mutex_unlock(&mutex_q2);
    }
    fclose(f);
}

/*  ОУ2:
    на основе массива сумм по группам выбирает группу с наименьшей суммой 
    вставляет число в массив чисел этой группы с учетом сортировки
    записывает номер этой группы в Q3   */
void *define_into_group(void *arg) {
    (void) arg;

    pair_t *pair;
    for (size_t k = 0; k < N; ++k) {
        int rc = -1;
        void *data;
        while (rc != 0) {
            pthread_mutex_lock(&mutex_q2);
            rc = get(&q2, &data);
            pthread_mutex_unlock(&mutex_q2);
        }
        pair = (pair_t *)data;
        printf("get pair = %s : %d\n", pair->key, pair->num);

        // выбор группы с наименьшей суммой 
        size_t ind_group = 0;
        int min_sum = groups[0].sum;
        for (size_t i = 1; i < N; ++i)
            if (groups[i].sum < min_sum) {
                ind_group = i;
                min_sum = groups[i].sum;
            }
        printf("ind_group = %ld, min_sum = %d\n", ind_group, min_sum);
        
        // вставка числа в массив чисел этой группы с учетом сортировки
        pair_t *tmppair = pair;
        pair_t **arr = groups[ind_group].pairs;

        // printf("---%d\n", groups[0].pairs[0]->num);
        // printf("---%d\n", arr[0]->num);
        
        size_t i = 0;
        while (i < groups[ind_group].len_pars && tmppair->num > arr[i]->num) {
            pair_t *tmp = tmppair;
            tmppair = arr[i];
            arr[i] = tmp;
            ++i;
            printf("see  %s : %d\n", tmp->key, tmp->num);
            assert(i < MAX_COUNT_PAIRS);
        }
        arr[i] = tmppair;
        ++groups[ind_group].len_pars;
        groups[ind_group].sum += pair->num;
        print_groups();

        // записывает номер этой группы в Q3
        pthread_mutex_lock(&mutex_q3);
        assert(put(&q3, &ind_group) == 0);
        // printf("put ind_group = %ld\n", ind_group);
        pthread_mutex_unlock(&mutex_q3);
    }   
}

/*  ОУ3:
    открывает файл группы = номеру полученной группы
    перезаписывает его полностью с учетом новой суммы и новой последовательности группы */
void *write_pair(void *arg) {
    (void) arg;

    size_t ind_group;
    char filename[50], ssum[10], str[MAX_LEN_KEY * 2 + 10];
    for (size_t k = 0; k < N; ++k) {
        int rc = -1;
        size_t *tmp;
        while (rc != 0) {
            pthread_mutex_lock(&mutex_q3);
            rc = get(&q3, (void *) &tmp);
            pthread_mutex_unlock(&mutex_q3);
        }
        ind_group = *tmp;
        printf("ind_group = %ld\n", ind_group);

        sprintf(filename, "data_out/group_%ld.txt", ind_group);
        FILE *f = fopen(filename, "w");
        assert(f != NULL);

        sprintf(ssum, "%d", groups[ind_group].sum);
        fputs(ssum, f);

        for (size_t i = 0; i < groups[ind_group].len_pars; ++i) {
            sprintf(str, "%s : %d\n", groups[ind_group].pairs[i]->key, groups[ind_group].pairs[i]->num);
            fputs(str, f);
        }
    }
}

int main() {
    q1.head = NULL;
    q1.tail = NULL;
    q2.head = NULL;
    q2.tail = NULL;
    q3.head = NULL;
    q3.tail = NULL;
    for (size_t i = 0; i < N; ++i) {
        groups[i].sum = 0;
        groups[i].len_pars = 0;
    }

    char filename[] = "./data_in/data_in.txt";
    assert(put(&q1, &(filename[0])) == 0);

    void *v = NULL;
    read_pair(v);
    // print_queue(&q2, 2);
    define_into_group(v);
    // printf("HERE 2\n");
    // write_pair(v);

    return 0;
}

/*
Q1: FILE arr[]
    put - openfile
    get - return FILE * указ на строку которую надо считать
ОУ1: 
    read_str from file 
    создать на ее основе struct pair
    положить struct pair в очередь Q2
Q2: pair_t arr[]
    put - struct pair
    get - struct pair
ОУ2:
    на основе массива сумм по группам выбирает группу с наименьшей суммой 
    вставляет число в массив чисел этой группы с учетом сортировки
    записывает номер этой группы в Q3
Q3: int arr[]
    put - номер группы
    get - номер группы
ОУ3:
    открывает файл группы = номеру полученной группы
    перезаписывает его полностью с учетом новой суммы и новой последовательности группы
*/
