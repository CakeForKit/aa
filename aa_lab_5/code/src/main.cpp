
#include "queue.h"

pthread_mutex_t mutex_q2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_q3 = PTHREAD_MUTEX_INITIALIZER;
std::queue<std::string> q1;
std::queue<pair_t> q2;
std::queue<size_t> q3;
std::vector<group_t> groups;
long int start_time = 0;

FILE *f1, *f2, *f3;

void print_groups() {
    int i = 0;
    for (group_t gr : groups) {
        std::cout << i << ": sum=" << gr.sum << ": ";
        ++i;
        for (pair_t p : gr.pairs) {
            std::cout << p.num << " ";
        }
        std::cout << "\n";
    }
}

// вычисляет разность времени в микросекундах
long int calc_elapsed_time(const struct timeval *beg, const struct timeval *end)
{
    return ((end->tv_sec - beg->tv_sec) * 1000 * 1000 +
            end->tv_usec - beg->tv_usec);
}

long int msc(const struct timeval *time) {
    return (time->tv_sec * 1000 * 1000 + time->tv_usec - start_time);
}

long int avg(std::vector<long int> arr) {
    long int s = 0;
    for (long int elem : arr)
        s += elem;
    return s / static_cast<long int>(arr.size());
}

/*  ОУ1: 
    read_str from file 
    создать на ее основе struct pair
    положить struct pair в очередь Q2   */
void *read_pair(void *arg) {
    (void) arg;

    char str[100];
    struct timeval t_beg, t_end;
    FILE *flog = fopen("./log/p1_log.txt", "w");
    assert(flog != NULL);

    std::string fn = q1.front();
    FILE *f = fopen(fn.c_str(), "r");
    assert(f != NULL);

    pair_t p;
    int rc = 0;
    while (rc != EOF) {
        gettimeofday(&t_beg, NULL);

        rc = fscanf(f, "%s : %d\n", &(p.key[0]), &p.num);
        // sleep(0.0000000000000001);
        if (rc != EOF) {

            pthread_mutex_lock(&mutex_q2);
            q2.push(p);
            gettimeofday(&t_end, NULL);
            pthread_mutex_unlock(&mutex_q2);
            
            sprintf(str, "%ld %ld\n", msc(&t_beg), msc(&t_end));
            fputs(str, flog);
        }
    }
    fclose(f);
    return NULL;
}

/*  ОУ2:
    на основе массива сумм по группам выбирает группу с наименьшей суммой 
    вставляет число в массив чисел этой группы с учетом сортировки
    записывает номер этой группы в Q3   */
void *define_into_group(void *arg) {
    (void) arg;

    char str[100];
    struct timeval t_beg, t_end;
    FILE *flog = fopen("./log/p2_log.txt", "w");
    assert(flog != NULL);

    pair_t *pair;
    for (size_t k = 0; k < COUNT_PAIRS; ++k) {
        pair_t pair;
        bool get_elem = false;
        while (!get_elem) {
            pthread_mutex_lock(&mutex_q2);
            gettimeofday(&t_beg, NULL);
            if (q2.size() > 0) {
                pair = q2.front();
                q2.pop();
                get_elem = true;
            }
            pthread_mutex_unlock(&mutex_q2);
        }
        if (DEBUG)
            printf("%ld: get pair = %s : %d\n", k, pair.key, pair.num);

        // выбор группы с наименьшей суммой 
        size_t ind_group = 0;
        int min_sum = groups[0].sum;
        for (size_t i = 1; i < N; ++i)
            if (groups[i].sum < min_sum) {
                ind_group = i;
                min_sum = groups[i].sum;
            }
        if (DEBUG)
            printf("ind_group = %ld, min_sum = %d\n", ind_group, min_sum);
        
        // вставка числа в массив чисел этой группы с учетом сортировки
        if (groups[ind_group].pairs.size() == 0) {
            groups[ind_group].pairs.push_back(pair);
            groups[ind_group].sum += pair.num;
        } else {
            bool out = false;
            for (std::vector<pair_t>::iterator it = groups[ind_group].pairs.begin(); 
                !out && it < groups[ind_group].pairs.end(); ++it) {
                // std::cout << "see " << (*it).num << "\n";
                if (strcmp((*it).key, pair.key) >0) {
                // if ((*it).num > pair.num) {
                    groups[ind_group].pairs.insert(it, pair);
                    groups[ind_group].sum += pair.num;
                    out = true;
                }
            }
            if (!out) {
                groups[ind_group].pairs.push_back(pair);
                groups[ind_group].sum += pair.num;
            }
        }
        if (DEBUG)
            print_groups();

        // записывает номер этой группы в Q3
        pthread_mutex_lock(&mutex_q3);
        q3.push(ind_group);
        gettimeofday(&t_end, NULL);
        pthread_mutex_unlock(&mutex_q3);
        sprintf(str, "Q3 unlock: %ld\n", msc(&t_end));
        fputs(str, f2);
        
        sprintf(str, "%ld %ld\n", msc(&t_beg), msc(&t_end));
        fputs(str, flog);
    }   
    return NULL;
}

/*  ОУ3:
    открывает файл группы = номеру полученной группы
    перезаписывает его полностью с учетом новой суммы и новой последовательности группы */
void *write_pair(void *arg) {
    (void) arg;
    char strlog[100];
    struct timeval t_beg, t_end;
    FILE *flog = fopen("./log/p3_log.txt", "w");
    assert(flog != NULL);
    
    size_t ind_group;
    char filename[50], ssum[10], str[MAX_LEN_KEY * 2 + 10];
    for (size_t k = 0; k < COUNT_PAIRS; ++k) {
        gettimeofday(&t_beg, NULL);
        sprintf(filename, "p3 try open q3: %ld\n", msc(&t_beg));
        fputs(filename, f3);
        bool get_elem = false;
        while (!get_elem) {
            pthread_mutex_lock(&mutex_q3);
            gettimeofday(&t_beg, NULL);     
            sprintf(filename, "            q3: %ld\n", msc(&t_beg));
            fputs(filename, f3);
            if (q3.size() > 0) {
                ind_group = q3.front();
                q3.pop();
                get_elem = true;
            }
            pthread_mutex_unlock(&mutex_q3);
        }
        if (DEBUG)
            printf("ind_group = %ld\n", ind_group);

        sprintf(filename, "data_out/group_%ld.txt", ind_group);
        FILE *f = fopen(filename, "w");
        assert(f != NULL);

        sprintf(ssum, "%d\n", groups[ind_group].sum);
        fputs(ssum, f);

        for (pair_t p : groups[ind_group].pairs) {
            sprintf(str, "%s : %d\n", p.key, p.num);
            fputs(str, f);
        }
        fclose(f);
        gettimeofday(&t_end, NULL);
        sprintf(strlog, "%ld %ld\n", msc(&t_beg), msc(&t_end));
        fputs(strlog, flog);
    }
    return NULL;
}

int main() {
    f1 = fopen("./tmp1.txt", "w");
    f2 = fopen("./tmp2.txt", "w");
    f3 = fopen("./tmp3.txt", "w");

    std::string filename = "./data_in/data_in.txt";
    q1.push(filename);

    for (size_t i = 0; i < N; ++i) {
        group_t gr = {0, std::vector<pair_t>()};
        groups.push_back(gr);
    }

    void *v = NULL;
    struct timeval t_beg, t_end;
    if (!PARALLEL) {
        gettimeofday(&t_beg, NULL);

        read_pair(v);
        define_into_group(v);
        write_pair(v);

        gettimeofday(&t_end, NULL);
        std::cout << "not par time = " << calc_elapsed_time(&t_beg, &t_end) << "\n";
    } else {
        gettimeofday(&t_beg, NULL);
        start_time = msc(&t_beg);
        int rc, countThreads = 3;
        //выделяем память под массив идентификаторов потоков
        pthread_t* threads = static_cast<pthread_t*>(malloc(countThreads * sizeof(pthread_t)));
        assert(threads != NULL);
        
        assert(pthread_create(&(threads[2]), NULL, &write_pair, NULL) == 0);
        assert(pthread_create(&(threads[1]), NULL, &define_into_group, NULL) == 0);
        assert(pthread_create(&(threads[0]), NULL, &read_pair, NULL) == 0);
        
        

        //ожидаем выполнение всех потоков
        for(int k = 0; k < countThreads; ++k)
            pthread_join(threads[k], NULL);

        gettimeofday(&t_end, NULL);
        std::cout << "par time = " << calc_elapsed_time(&t_beg, &t_end) << "\n";
    }
    

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
