
set ns [new Simulator]


set nf [open out.nam w]
$ns namtrace-all $nf

$ns color 1 Blue
$ns color 1 Red

proc finish {} {
        global ns nf
        $ns flush-trace
	
        close $nf
	
        exec nam out.nam &
        exit 0
}

set n5 [$ns node]
set n1 [$ns node]

$ns duplex-link $n5 $n1 1Mb 10ms DropTail


set udp0 [new Agent/UDP]
$ns attach-agent $n5 $udp0


set cbr0 [new Application/Traffic/CBR]
$cbr0 set packetSize_ 500
$cbr0 set interval_ 0.005
$cbr0 attach-agent $udp0


set null0 [new Agent/Null]
$ns attach-agent $n1 $null0


$ns connect $udp0 $null0  


$ns at 0.5 "$cbr0 start"
$ns at 4.5 "$cbr0 stop"

$ns at 5.0 "finish"

puts "CBR packet size = [$cbr0 set packet_size_]"
puts "CBR interval = [$cbr0 set interval_]"


#Run the simulation
$ns run
