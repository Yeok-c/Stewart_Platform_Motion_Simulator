clear all;
open('Shadow box.csv')
% open('Burpee.csv')
Badminton = Shadowbox
%%
Badminton_ = table2array(Badminton)
Badminton_ = str2double(Badminton_(2:1500,3:14))

%
Badminton_ = (Badminton_ - mean(Badminton_,1))

% for i = 1:12
%     subplot(12,1,i); plot(Badminton_(:, i))
% end
% range(Badminton)
% Badminton_ = Badminton_ ./std(Badminton_)
%
% Badminton__(:,3) = Badminton_(:,1)
% Badminton__(:,2) = Badminton_(:,2)
% Badminton__(:,1) = Badminton_(:,3)
% Badminton_(:,1:3) = Badminton__(:,1:3)

Badminton__ = Badminton_(:,[1:6])-Badminton_(:,[7:12])


Badminton__(:,4:6) = Badminton__(:,4:6)./4
% Badminton__ = bandpass(Badminton__, 2000, 20)

for i = 1:6
    [Badminton__(:, i), ~] = lowpass(Badminton__(:, i), 20, 100);
    subplot(6,1,i); plot(Badminton__(:, i))
end

for i = length(Badminton__)
    Badminton__(:, 1:3)= [rotz(30)*Badminton__(:, 1:3)']' ;
end


writematrix(Badminton__,'Badminton_r.csv')