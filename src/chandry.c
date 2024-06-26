#include "philo.h"

typedef enum {
    THINKING,
    HUNGRY,
    EATING
} philo_state_t;

typedef struct {
    philo_state_t state;
    int left_fork;
    int right_fork;
    pthread_cond_t self_cond;
    pthread_mutex_t self_mutex;
} philo_t;

void test(philo_t *philo, t_data *data) {
    if (philo->state == HUNGRY &&
        (data->forks[philo->left_fork] == 0 || data->forks[philo->left_fork] == philo->right_fork + 1) &&
        (data->forks[philo->right_fork] == 0 || data->forks[philo->right_fork] == philo->left_fork + 1)) {
        data->forks[philo->left_fork] = philo->right_fork + 1;
        data->forks[philo->right_fork] = philo->left_fork + 1;
        philo->state = EATING;
        printf("%ld %d is eating\n", get_timestamp(data), philo->right_fork + 1);
    }
}

void take_forks(philo_t *philo, t_data *data, int idx) {
    pthread_mutex_lock(&philo->self_mutex);
    philo->state = HUNGRY;
    test(philo, data);
    if (philo->state != EATING)
        pthread_cond_wait(&philo->self_cond, &philo->self_mutex);
    pthread_mutex_unlock(&philo->self_mutex);
}

void put_forks(philo_t *philo, t_data *data) {
    pthread_mutex_lock(&philo->self_mutex);
    philo->state = THINKING;
    test(philo, data);
    pthread_mutex_unlock(&philo->self_mutex);
}

void *philo_thread(void *arg) {
    t_data *data = (t_data *)arg;
    philo_t *philo = &data->philos[data->philo_idx];
    philo->left_fork = data->philo_idx;
    philo->right_fork = (data->philo_idx + 1) % data->num_philo;

    while (!data->dead_philo && !all_finished(data)) {
        take_forks(philo, data, data->philo_idx);
        philo_wait(data, data->time_to_eat);
        put_forks(philo, data);
        philo_wait(data, data->time_to_sleep);
    }

    return NULL;
}