#Bus

set ns [new Simulator]
$ns color 1 Green


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
set n5 [$ns node]
set n6 [$ns node]
set n7 [$ns node]

$n1 color Yellow
$n3 color Blue


$ns duplex-link $n0 $n1 1Mb 10ms DropTail
$ns duplex-link $n1 $n2 1Mb 10ms DropTail
$ns duplex-link $n2 $n3 1Mb 10ms DropTail
$ns duplex-link $n3 $n4 1Mb 10ms DropTail
$ns duplex-link $n1 $n5 1Mb 10ms DropTail
$ns duplex-link $n2 $n6 1Mb 10ms DropTail
$ns duplex-link $n3 $n7 1Mb 10ms DropTail


$ns duplex-link-op $n0 $n1 orient right
$ns duplex-link-op $n1 $n2 orient right
$ns duplex-link-op $n2 $n3 orient right
$ns duplex-link-op $n3 $n4 orient right
$ns duplex-link-op $n1 $n5 orient up
$ns duplex-link-op $n2 $n6 orient down
$ns duplex-link-op $n3 $n7 orient up



set tcp0 [new Agent/TCP]
$tcp0 set class_ 1
$ns attach-agent $n1 $tcp0

set sink0 [new Agent/TCPSink]
$ns attach-agent $n3 $sink0

$ns connect $tcp0 $sink0

set cbr0 [new Application/Traffic/CBR]
$cbr0 set packetSize_ 1000
$cbr0 set interval_ 0.05
$cbr0 attach-agent $tcp0

$ns at 0.5 "$cbr0 start"
$ns at 4.5 "$cbr0 stop"

$ns at 5.0 "finish"
$ns run
