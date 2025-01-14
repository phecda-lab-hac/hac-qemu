#ifndef INTERRUPT_ROUTER_H
#define INTERRUPT_ROUTER_H

#include "qemu/thread.h"
#include "exec/memattrs.h"
#include "io/channel-socket.h"

typedef struct {
    Object parent_obj;
    QemuThread thread;
    int thread_id;
} IORouter;

struct io_router_loop_arg {
    QEMUFile *req_file;
    QEMUFile *rsp_file;
    QIOChannel *channel;
};

void start_io_router(void);
void disconnect_io_router(void);

extern QemuMutex ipi_mutex;
extern int pr_debug_log;
int pr_debug(const char *format, ...);

int parse_cluster_iplist(const char *cluster_iplist);
char **get_cluster_iplist(uint32_t *len);

void shutdown_forwarding(void);
void reset_forwarding(void);
void irq_forwarding(int cpu_index, int vector_num, int trigger_mode);
void special_interrupt_forwarding(int cpu_index, int mask);
void startup_forwarding(int cpu_index, int vector_num);
void init_level_deassert_forwarding(int cpu_index);
void lapic_forwarding(int cpu_index, hwaddr addr, uint32_t val);
void eoi_forwarding(int isrv);
void mmio_forwarding(hwaddr addr, MemTxAttrs attrs, uint8_t *buf, int len, bool is_write);
void pio_forwarding(uint16_t port, MemTxAttrs attrs, void *data, int direction, int size, uint32_t count, bool broadcast);
void kvmclock_fetching(uint64_t *kvmclock);

#endif /* INTERRUPT_ROUTER_H */
