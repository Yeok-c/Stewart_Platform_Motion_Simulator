clear all; cd('D:\Github\MCU_App\Stewart_Platform_Motion_Simulator\motion_capture')
open('Box Jump 2.csv')
% open('Burpee.csv')

%%
exercise_ = Boxjump2(10:end-10,1:6);
% [-movements[ix,3],movements[ix,1],movements[ix,2]
exercise_(:,1:3) = [-exercise_(:,3), exercise_(:,1), exercise_(:,2)]
% 
offset = [110, -0, -150];
% offset = [0, 0, 0];
exercise_(:,1) = exercise_(:,1)+offset(1)
exercise_(:,2) = exercise_(:,2)+offset(2)
exercise_(:,3) = exercise_(:,3)+offset(3)

exercise_(:,2) = exercise_(:,2)/2
exercise_(:,3) = exercise_(:,3)/2

exercise_(:,4:6) = exercise_(:,4:6)./16 % Scale Trans down by body ratio
exercise_(:,4:6) = exercise_(:,4:6)-median(exercise_(:,4:6))

labels = {'RX',	'RY',	'RZ',	'TX',	'TY',	'TZ'};
%
figure(1);
for i = 1:6
%     [exercise_(:, i), ~] = lowpass(exercise_(:, i), 20, 100);
    subplot(6,1,i); plot(exercise_(:, i));
    ylabel(labels{i});
end
% subplot(6,1,1); title('Subject1:Kinematics, World Root')
subplot(6,1,1); title('Subject1:Segments: LowerBack')

%%
exercise__ = exercise_(1:1600,:)
writematrix(exercise_,'Box_Jump.csv')