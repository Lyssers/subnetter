# Subnetter

Useful for network admin and pentesting to get a quick and easy summary of a network

1. Compile with gcc like:

`gcc subnetter.c -o subnetter.o

2. Run like:

`./subnetter.o 192.168.0.30 255.255.255.0

3. Output:

```
This is subnetter
Arguments passed: 2

IP Address: 192.168.0.30
NetMask: 255.255.255.0

Decimal IP: 3232235550
Decimal Netmask: 4294967040

Decimal Network Starting Address: 3232235520

Starting address is:
192.168.0.1

Decimal Network Last Address: 3232235775

Last Address is:
192.168.0.255

Usable Hosts: 255
```

Optional: `sudo cp ./subnetter.o /usr/bin/subnetter` to run it with just `subnetter`

Output is very verbose by default which works for my need, if you'd like a more parseable mode please let me know!

Alternatively use `tail` and `awk`like e.g. with [cidr2mask](https://github.com/Lyssers/cidr2mask/)

```
echo $(ifconfig wlan0 | grep 'inet' | head -1 | awk -F ' ' '{print $2}')  $(cidr2mask 24 | tail -1 |  awk -F ': ' '{print $2}') | xargs subnetter | tail -1 | awk -F ': ' '{print $2}'
```

The above outputs usable hosts for the wlan0 network interace
