total_clusters = 50;
total_files = total_clusters - 1;

        %array = csvread ('C:\Users\Rooshan.Rooshan-PC\Documents\Visual Studio 2015\Projects\ConsoleApplication2\ConsoleApplication2\points.cvs');
        %col1 = array (:, 1);
        %col2 = array (:, 2);
        %hold on;
        %scatter (col1, col2, [], 'x');

for k = 0: total_files
    %load 'C:\Users\Rooshan.Rooshan-PC\Documents\GitHub\CS401Projects\TheProblem(Kmeans)\ParallelKmeans\ParallelKmeans\plotcuster'num2str(k)'.txt';
    outputfile = sprintf('C:\\Users\\Rooshan.Rooshan-PC\\Documents\\GitHub\\CS401Projects\\TheProblem(Kmeans)\\ParallelKmeans\\ParallelKmeans\\plotcuster%i.csv',k);
    load (outputfile);
    scatterfile = sprintf('plotcuster%i', k);
    
    getvalue = evalin('base', scatterfile);
    
    if (isempty(getvalue)~= 1)
        hold on;
        scatter3(getvalue(:,1), getvalue(:,2), getvalue(:,3), 'filled');
    end    
end


