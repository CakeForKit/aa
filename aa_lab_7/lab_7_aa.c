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
            get_elem = true; }
        pthread_mutex_unlock(&mutex_q3); }
    sprintf(filename, "data_out/group_%ld.txt", ind_group);
    FILE *f = fopen(filename, "w");
    assert(f != NULL);
    sprintf(ssum, "%d\n", groups[ind_group].sum);
    fputs(ssum, f);
    for (pair_t p : groups[ind_group].pairs) {
        sprintf(str, "%s : %d\n", p.key, p.num);
        fputs(str, f); }
    fclose(f);
    gettimeofday(&t_end, NULL);
    sprintf(strlog, "%ld %ld\n", msc(&t_beg), msc(&t_end));
    fputs(strlog, flog); }

















pair_t pair {'qwe', 2};
ind = 10;        // вставка числа в массив чисел этой группы с учетом сортировки
if (groups[ind].pairs.size() == 0) {                                        
    groups[ind].pairs.push_back(pair);                                     
    groups[ind].sum += pair.num;                                            
} else 
{ bool out = false;
    for (std::vector<pair_t>::iterator it = groups[ind].pairs.begin(); 
        !out && it < groups[ind].pairs.end(); ++it) {
        if (strcmp((*it).key, pair.key) >0) {
            groups[ind].pairs.insert(it, pair);
            groups[ind].sum += pair.num;
            out = true;
        }
    }
    if (!out) {
        groups[ind].pairs.push_back(pair);
        groups[ind].sum += pair.num;
    }
}



struct pair_t {
    char key[MAX_LEN_KEY];
    int num;
};

struct group_t
{
    int sum;
    std::vector<pair_t> pairs;
};