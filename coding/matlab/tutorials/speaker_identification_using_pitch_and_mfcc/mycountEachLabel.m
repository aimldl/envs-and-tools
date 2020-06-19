function datastoreCount = mycountEachLabel( datastore )

    [datastoreCount, datastoreCount.Count,~] = unique( datastore.Labels );
%     datastoreCount =
% 
%       8×2 table
% 
%         Label     Count
%         ______    _____
% 
%         'fejs'        1
%         'fmjd'     1902
%         'fsrb'     4194
%         'ftmj'     6368
%         'fwxs'     8343
%         'mcen'    10405
%         'mrcb'    11952
%         'msjm'    13356
end