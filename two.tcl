set ns [new Simulator] 

# Open the Trace file 
set ntrace [open ex2.tr w] 
$ns trace-all $ntrace 
set namtrace [open ex2.nam w] 
$ns namtrace-all $namtrace 

# Finish procedure 
proc finish {} { 
global ns ntrace namtrace 
$ns flush-trace 
close $ntrace 
close $namtrace 
exec nam ex2.nam & 
exit 0 
} 

# Create four nodes 
set n0 [$ns node] 
set n1 [$ns node] 
set n2 [$ns node] 
set n3 [$ns node] 

$ns color 1 Blue 
$ns color 2 Red 

# Create links between the nodes 
$ns duplex-link $n0 $n2 2Mb 10ms DropTail 
$ns duplex-link $n1 $n2 2Mb 10ms DropTail 
$ns simplex-link $n2 $n3 0.07Mb 20ms DropTail 
$ns simplex-link $n3 $n2 0.07Mb 20ms DropTail 

# Set Queue Size of link (n2-n3) to 10 
$ns queue-limit $n2 $n3 3 

# Monitor the queue for link (n2-n3) 
$ns simplex-link-op $n2 $n3 queuePos 0.5 

# Setup a TCP connection 
set tcp [new Agent/TCP/Newreno] 
$ns attach-agent $n0 $tcp 
 
set sink [new Agent/TCPSink/DelAck] 
$ns attach-agent $n3 $sink 
$ns connect $tcp $sink 

$tcp set fid_ 1 
#$tcp set class_ 1 


# Setup a FTP over TCP connection 
set ftp [new Application/FTP] 
$ftp attach-agent $tcp 

#$ftp set type_ FTP 
$ftp set type_ FTP 
$ftp set packetSize_ 1000 
$ftp set rate_ 1Mb 
$ftp set random_ false 

# Setup a UDP connection 
set udp [new Agent/UDP] 
$ns attach-agent $n1 $udp 

set null [new Agent/Null] 
$ns attach-agent $n3 $null 
$ns connect $udp $null 
$udp set fid_ 2 
#$udp set class_ 2 


# Setup a CBR over UDP connection 
set cbr [new Application/Traffic/CBR] 
$cbr attach-agent $udp 
$cbr set type_ CBR 
$cbr set packetSize_ 1000 
$cbr set rate_ 1Mb 
$cbr set random_ false 

$ns at 1.0 "$cbr start" 
$ns at 1.0 "$ftp start" 
$ns at 24.0 "$ftp stop" 
$ns at 24.0 "$cbr stop" 

$ns at 25.0 "finish" 

$ns run 


