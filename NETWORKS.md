## OVERVIEW


### ETA Files

Eta files are timestamped files that have a record of the network from a starting point. 

So if my eta file starts at 1716723772, it is named 1716723772.eta and has a list of events starting from that UNIX timestamp. 

A real file format can be including the timestamp as the header and naming it whatever is conveniant for network location. 

So, in the future we make the file as:

---

1716723772

...
CH(I)[2587]: A1
CH(I)[pc:1438]:
CH(I)[2587]: G-167
CH(I)[2587]: I-111
CH(I)[2587]: T-111
CH(I)[2587]: A-111
CH(I)[2587]: G1
CH(I)[2587]: I1
CH(I)[2587]: T1
...


1716723772 + x(s)

---

where  x(s) is a real number like 4000(s)
