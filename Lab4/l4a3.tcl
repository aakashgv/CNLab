#Star


set ns [new Simulator]
$ns color 1 Orange

set nf [open out.nam w]
$ns namtrace-all $nf


proc finish {} {
 global ns nf
 $ns flush-trace
 close $nf
 exec nam out.nam &
 exit 0
}

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]

$n1 color Red
$n3 color Yellow


$ns duplex-link $n0 $n1 1Mb 10ms DropTail
$ns duplex-link $n0 $n2 1Mb 10ms DropTail
$ns duplex-link $n0 $n3 1Mb 10ms DropTail
$ns duplex-link $n0 $n4 1Mb 10ms DropTail

$ns duplex-link-op $n0 $n1 orient right-up
$ns duplex-link-op $n0 $n2 orient right-down
$ns duplex-link-op $n0 $n3 orient left-down
$ns duplex-link-op $n0 $n4 orient left-up

set tcp0 [new Agent/TCP]
$tcp0 set class_ 1
$ns attach-agent $n1 $tcp0

set sink0 [new Agent/TCPSink]
$ns attach-agent $n1 $sink0

$ns connect $tcp0 $sink0

set cbr0 [new Application/Traffic/CBR]
$cbr0 set packetSize_ 100
$cbr0 set interval_ 0.05
$cbr0 attach-agent $tcp0
$ns at 0.5 "$cbr0 start"
$ns at 4.5 "$cbr0 stop"

$ns at 5.0 "finish"
#Run the simulation
$ns run
