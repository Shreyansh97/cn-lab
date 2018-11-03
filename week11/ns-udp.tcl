set ns [new Simulator]
set nf [open out.nam w]
$ns namtrace-all $nf

set tr [open udp-160k.tr w]
$ns trace-all $tr

proc finish {} {
	global ns nf tr
	$ns flush-trace
	close $nf
	close $tr
	# exec nam out.nam &
	# exec xgraph udp-120.tr -geometry 800x400 &
	exit 0
}

set s [$ns node]
set r [$ns node]
set d [$ns node]

# proc record {} {
# 	global s r d tr
# 	set ns [Simulator instance]
# 	set time 0.5
# 	set bw0 [$d set bytes_]
# 	set now [$ns now]
# 	puts $tr "$now [expr]"
# }

$ns duplex-link $s $r 1Mb 50ms DropTail
$ns duplex-link $r $d 100Kb 5ms DropTail
$ns duplex-link-op $s $r orient right
$ns duplex-link-op $r $d orient right
$ns queue-limit $r $d 10
$ns duplex-link-op $r $d queuePos 0.5

set udp [new Agent/UDP]
$ns attach-agent $s $udp

set cbr0 [new Application/Traffic/CBR]
$cbr0 attach-agent $udp
$cbr0 set type_ CBR
$cbr0 set packetSize_ 100
$cbr0 set interval_ 0.005

set null0 [new Agent/Null]
$ns attach-agent $d $null0
$ns connect $udp $null0

$ns at 0.1 "$cbr0 start"
$ns at 10.1 "$cbr0 stop"
$ns at 10.5 "finish"
$ns run