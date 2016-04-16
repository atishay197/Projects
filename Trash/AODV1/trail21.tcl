set val(chan)         Channel/WirelessChannel  ;# channel type
 set val(prop)         Propagation/TwoRayGround ;# radio-propagation model
 set val(ant)          Antenna/OmniAntenna      ;# Antenna type
 set val(ll)           LL                       ;# Link layer type
 set val(ifq)          Queue/DropTail/PriQueue  ;# Interface queue type
 set val(ifqlen)       50                       ;# max packet in ifq
 set val(netif)        Phy/WirelessPhy          ;# network interface type
 set val(mac)          Mac/802_11               ;# MAC type
 set val(nn)           6                        ;# number of mobilenodes
 set val(rp)           AODV                     ;# routing protocol
 set val(x)            800
 set val(y)            800




set ns [new Simulator]
#ns-random 0

set f [open new2.tr w]
$ns trace-all $f
set namtrace [open new2.nam w]
$ns namtrace-all-wireless $namtrace $val(x) $val(y)
set topo [new Topography]
$topo load_flatgrid 800 800

create-god $val(nn)

set chan_1 [new $val(chan)]
set chan_2 [new $val(chan)]
set chan_3 [new $val(chan)]
set chan_4 [new $val(chan)]
set chan_5 [new $val(chan)]
set chan_6 [new $val(chan)]

# CONFIGURE AND CREATE NODES

$ns node-config  -adhocRouting $val(rp) \
          -llType $val(ll) \
                 -macType $val(mac) \
                 -ifqType $val(ifq) \
                 -ifqLen $val(ifqlen) \
                 -antType $val(ant) \
                 -propType $val(prop) \
                 -phyType $val(netif) \
                 #-channelType $val(chan) \
                 -topoInstance $topo \
                 -agentTrace ON \
                 -routerTrace ON \
                 -macTrace ON \
                 -movementTrace OFF \
                 -channel $chan_1

proc finish {} {
    global ns namtrace 
    $ns flush-trace
        close $namtrace 
        exec nam -r 5m new2.nam &
    exit 0
}

# define color index
$ns color 0 blue
$ns color 1 red
$ns color 2 chocolate
$ns color 3 red
$ns color 4 brown
$ns color 5 tan
$ns color 6 gold
$ns color 7 black
                      
set n(0) [$ns node]
$ns at 0.0 "$n(0) color blue"
$n(0) color "0"
$n(0) shape "circle"
set n(1) [$ns node]
$ns at 0.0 "$n(1) color red"
$n(1) color "blue"
$n(1) shape "circle"
set n(2) [$ns node]
$n(2) color "tan"
$n(2) shape "circle"
set n(3) [$ns node]
$n(3) color "red"
$n(3) shape "circle"
set n(4) [$ns node]
$n(4) color "tan"
$n(4) shape "circle"
set n(5) [$ns node]
$ns at 0.0 "$n(5) color blue"
$n(5) color "red"
$n(5) shape "circle"


for {set i 0} {$i < $val(nn)} {incr i} {
    $ns initial_node_pos $n($i) 30+i*100
    }
$ns at 1.1 "[$n(1) set ragent_] malicious"  
        
$ns at 0.0 "$n(0) setdest 200.0 400.0 3000.0"
$ns at 0.0 "$n(1) setdest 400.0 245.0 3000.0"
$ns at 0.0 "$n(2) setdest 400.0 150.0 3000.0"
$ns at 0.0 "$n(3) setdest 400.0 200.0 3000.0"
$ns at 0.0 "$n(4) setdest 400.0 250.0 3000.0"
$ns at 0.0 "$n(5) setdest 600.0 400.0 3000.0"

$ns at 1.0 "$n(1) setdest 400.0 400.0 1000.0"

$ns at 3.0 "$n(1) setdest 650.0 500.0 1000.0"

$ns at 3.0 "$n(3) setdest 400.0 400.0 1000.0"

$ns at 1.0 "$n(4) setdest 600.0 600.0 1000.0"

# CONFIGURE AND SET UP A FLOW

set sink0 [new Agent/LossMonitor]
set sink1 [new Agent/LossMonitor]
set sink2 [new Agent/LossMonitor]
set sink3 [new Agent/LossMonitor]
set sink4 [new Agent/LossMonitor]
set sink5 [new Agent/LossMonitor]
$ns attach-agent $n(0) $sink0
$ns attach-agent $n(1) $sink1
$ns attach-agent $n(2) $sink2
$ns attach-agent $n(3) $sink3
$ns attach-agent $n(4) $sink4
$ns attach-agent $n(5) $sink5

#$ns attach-agent $sink2 $sink3
set tcp0 [new Agent/TCP]
$ns attach-agent $n(0) $tcp0
set tcp1 [new Agent/TCP]
$ns attach-agent $n(1) $tcp1
set tcp2 [new Agent/TCP]
$ns attach-agent $n(2) $tcp2
set tcp3 [new Agent/TCP]
$ns attach-agent $n(3) $tcp3
set tcp4 [new Agent/TCP]
$ns attach-agent $n(4) $tcp4
set tcp5 [new Agent/TCP]
$ns attach-agent $n(5) $tcp5


proc attach-CBR-traffic { node sink size interval } {
   #Get an instance of the simulator
   set ns [Simulator instance]
   #Create a CBR  agent and attach it to the node
   set cbr [new Agent/CBR]
   $ns attach-agent $node $cbr
   $cbr set packetSize_ $size
   $cbr set interval_ $interval

   #Attach CBR source to sink;
   $ns connect $cbr $sink
   return $cbr
  }

set cbr0 [attach-CBR-traffic $n(0) $sink5 3000 .030]
$ns at 0.3 "$cbr0 start"
$ns at 10.5 "finish"
puts "Start of simulation.."
$ns run