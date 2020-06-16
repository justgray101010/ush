#include "ush.h"

static int arr_size(char **arr);
static void check_status(t_list **processes);
static void show_susp_list(t_list **processes, int fd);

int mx_jobs(char **args, int fd) {
    t_list **processes = mx_get_plist();

    if (arr_size(args) > 0) {
        fprintf(stderr, "jobs: too many arguments\n");
        return 1;
    }
    check_status(processes);
    show_susp_list(processes, fd);
    return 1;
}

static int arr_size(char **arr) {
    int result = 0;

    while (*arr) {
        result++;
        arr++;
    }
    return result;
}

static void check_status(t_list **processes) {
    pid_t ret_pid = 0;
    t_process *tmp = NULL;

    for (t_list *cur = *processes; cur; cur = cur->next) {
        tmp = (t_process*)cur->data;
        ret_pid = waitpid(tmp->pid, &tmp->status, WNOHANG | WUNTRACED);
        if (!MX_WIFSTOPPED(tmp->status) || ret_pid == -1) {
            mx_del_node_list(processes, &tmp);
        }
    }
}

static void show_susp_list(t_list **processes, int fd) {
    t_process *tmp = NULL;

    for (t_list *cur = *processes; cur; cur = cur->next) {
        tmp = (t_process*)cur->data;
        dprintf(fd, "[%d]    ", tmp->pos);
        dprintf(fd, "suspended  ");
        dprintf(fd, "%s\n", tmp->commands);
    }
}
