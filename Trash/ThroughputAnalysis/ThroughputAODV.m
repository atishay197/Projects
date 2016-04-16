% Atishay throughput analysis
% Import trace file
fid = fopen('final22.tr');
t = textscan(fid,'%s %f32 %d32 %s %s %d32 %s %d32 %s');
fid = fclose(fid);
% Storing size of packet recieved in packetSize
packetSize = t{8};
% storing time in matrix time
time = t{2};
% storing source node in matrix src
src = t{3};
%storing later at which packet generated at lyr
lyr = t{4};
%sequenceno in seq
seq = t{5};

% 2 conditions for calculation of simlple throughput
sent = strcmp(t{1},'s');
recieve = strcmp(t{1},'r');
dropped = strcmp(t{1},'D');
packetcbr = strcmp(t{7},'AODV');

packetLogicalArraysent = sent & packetcbr;
packetLogicalArrayrecieved = recieve & packetcbr;
packetLogicalArraydropped = dropped & packetcbr;

%sent, recieved and dropped packets
totalsent = sum(sent);
totalrecieved = sum(recieve);
totaldropped = sum(dropped);

throughputPacketssent = [packetSize(packetLogicalArraysent,1)];
throughputTimesent = [time(packetLogicalArraysent,1)];
throughputPacketsrecieved = [packetSize(packetLogicalArrayrecieved,1)];
throughputTimerecieved = [time(packetLogicalArrayrecieved,1)];
throughputPacketsdropped = [packetSize(packetLogicalArraydropped,1)];
throughputTimedropped = [time(packetLogicalArraydropped,1)];

totalpsent = sum(throughputPacketssent);
maxtimesent = max(throughputTimesent);
mintimesent = min(throughputTimesent);

totalprecieved = sum(throughputPacketsrecieved);
maxtimerecieved = max(throughputTimerecieved);
mintimerecieved = min(throughputTimerecieved);

totalpdropped = sum(throughputPacketsdropped);
maxtimedropped = max(throughputTimedropped);
mintimedropped = min(throughputTimedropped);

avgtpsent = 8*totalpsent/(maxtimesent - mintimesent)/1000;
avgtprecieved = 8*totalprecieved/(maxtimerecieved - mintimerecieved)/1000;
avgtpdropped = 8*totalpdropped/(maxtimedropped - mintimedropped)/1000;

plot (throughputTimesent,throughputPacketssent,'r-',throughputTimerecieved,throughputPacketsrecieved,'b-',throughputTimedropped,throughputPacketsdropped,'g+');
grid on;
xlabel ('Time (s)');
ylabel ('Throughput (kbps)');
legend('Sent Packets','Recieved Packets','Dropped Packets','Location','NorthEast');
gname1 = sprintf('Throughput Analysis\nAverage throughput::sent:%.0fkbps recieved:%.0fkbps dropped:%.0fkbps\nTotal Packets:: sent:%.0f recieved:%.0f dropped:%.0f  ',avgtpsent,avgtprecieved,avgtpdropped,totalpsent,totalprecieved,totalpdropped);
title(gname1);