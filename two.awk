BEGIN {
tcpcount=0;
udpcount=0;
}
{
pkttype= $5;
event= $1;
if(pkttype == "tcp") {
tcpcount++;
}
if(pkttype == "cbr") {
udpcount++;
}
}
END {
printf(" No. of tcp packets sent is %d\n", tcpcount);
printf(" No. of udp packets sent is %d\n", udpcount);
}
