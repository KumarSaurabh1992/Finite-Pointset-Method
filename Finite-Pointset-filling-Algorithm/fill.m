clear all;
clc;
close all;

load 'Points.txt'
hold on;
lab = 5;
k = 1;
lab_i = 0;
% for lab_i = 0:10
    for i = 1:size(Points,1)
        
        if(Points(i,5) == lab_i)
            plot(Points(i,1),Points(i,2),'*');
            k = i;
        else
           pause(0.1);
           lab_i = lab_i + 1;
        end
    end
% end
%      pause(0.01);
%     if(Points(i,5) == 1)
%         plot(Points(i,1),Points(i,2),'*');
%         
%         
%     end
% %     pause(0.01);
%     if(Points(i,5) == 2)
%         plot(Points(i,1),Points(i,2),'*');
%         
%         
%     end
%     pause(0.01);
%     if(Points(i,5) == 3)
%         plot(Points(i,1),Points(i,2),'*');
%        
%         
%     end
%     pause(0.01);
%     if(Points(i,5) == 4)
%         plot(Points(i,1),Points(i,2),'*');
%        
%         
%     end
%     pause(0.01);
% end