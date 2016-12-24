#Create simulator
set ns [new Simulator]
#Open the nam trace file
set nf [open ex1.nam w]
$ns namtrace-all $nf
set nt [open ex1.tr w]
$ns trace-all $nt
proc finish {} {
global ns nf nt
$ns flush-trace
#Close the trace file
close $nf
close $nt
#Execute nam on the trace file
exec nam ex1.nam &
exit 0
}
#create node
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
#create link
$ns duplex-link $n0 $n1 1Mb 10ms DropTail
$ns duplex-link $n1 $n2 0.4Mb 10ms DropTail
#Set Queue Size
$ns queue-limit $n0 $n1 10
$ns queue-limit $n1 $n2 10
#setup udp connection
set udp0 [new Agent/UDP]
$ns attach-agent $n0 $udp0
#set sink to node
set null0 [new Agent/Null]
$ns attach-agent $n2 $null0
#connect udp src and sink
$ns connect $udp0 $null0
set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp0
$cbr set type_ CBR
$cbr set packetSize_ 1000
$cbr set rate_ 0.5Mb
$cbr set random_ false
$ns at 0.0 "$cbr start"
$ns at 5.0 "finish"
$ns run
