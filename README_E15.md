# E15 — ARP Spoofing Detector (eBPF/XDP)

**Student:** Zahra Roozkhosh  
**Course:** Software Networks 2025-2026  
**Project:** E15 — ARP Spoofing Detector

## What I wanted to do

I had to write an eBPF program that can detect ARP packets on the network and read who sent them — basically their MAC address and IP address. ARP spoofing is when someone fakes their identity on a network, so this program is a basic way to monitor ARP traffic and see what's happening.

## What I did

First I set up Ubuntu on VMware. Then I installed clang, llvm, libelf-dev, libbpf-dev and iproute2. I wrote an eBPF program in C called arp_spoof.c that hooks at the XDP layer. When a packet comes in, it checks if it is an ARP packet. If it is, it reads the sender MAC and IP and prints them to the kernel log. Then I compiled it with clang, attached it to ens33 interface, and tested it with arping.

## Problems I had and how I fixed them

Problem 1: When I tried to compile, I got an error: asm/types.h file not found. I fixed it by installing gcc-multilib.

Problem 2: I could not copy paste from Windows into the Ubuntu VM. I fixed it by installing open-vm-tools and restarting the VM.

Problem 3: When I tried to push to GitHub, it said authentication failed. I learned that GitHub does not accept normal passwords anymore and you need a Personal Access Token.

Problem 4: git push origin main did not work because my branch was called master not main. I fixed it by using git push origin master.

## What I got

After running the program and sending ARP packets with arping, I could see them being detected in the trace pipe. Example output:

bpf_trace_printk: ARP: sender MAC=00:50:56:c0:00:08 IP=192.168.220.1

The program correctly identified the sender MAC address and IP for every ARP packet.

## What I learned

I learned how eBPF programs work at the XDP level and how packets are processed in the Linux network stack. I also learned how to compile and load eBPF programs and push code to GitHub.
