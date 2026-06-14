#include <linux/bpf.h>
#include <linux/if_ether.h>
#include <linux/if_arp.h>
#include <bpf/bpf_helpers.h>

SEC("xdp")
int arp_spoof_detector(struct xdp_md *ctx) {
    void *data = (void *)(long)ctx->data;
    void *data_end = (void *)(long)ctx->data_end;

    struct ethhdr *eth = data;
    if ((void *)(eth + 1) > data_end)
        return XDP_PASS;

    if (eth->h_proto != __constant_htons(ETH_P_ARP))
        return XDP_PASS;

    struct arphdr *arp = (void *)(eth + 1);
    if ((void *)(arp + 1) > data_end)
        return XDP_PASS;

    unsigned char *sender_mac = (unsigned char *)(arp + 1);
    unsigned char *sender_ip = sender_mac + 6;

    if (sender_mac + 6 > (unsigned char *)data_end)
        return XDP_PASS;
    if (sender_ip + 4 > (unsigned char *)data_end)
        return XDP_PASS;

    bpf_printk("ARP: sender MAC=%02x:%02x:%02x:%02x:%02x:%02x IP=%d.%d.%d.%d\n",
        sender_mac[0], sender_mac[1], sender_mac[2],
        sender_mac[3], sender_mac[4], sender_mac[5],
        sender_ip[0], sender_ip[1], sender_ip[2], sender_ip[3]);

    return XDP_PASS;
}

char _license[] SEC("license") = "GPL";
