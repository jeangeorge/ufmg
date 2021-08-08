disp('TP2 Algoritmos para Bioinformática')

% mude o nome do arquivo se necessario
filename = "E-MTAB-9221.aggregated_filtered_normalised_counts.mtx"

% passo 1
[A, rows, cols, entries] = mmread(filename);

% passo 2
B = A'*A;
lambda = eig(B);
lambda = sort (lambda, 'descend');

% passo 3
l = lambda.^(1/2);
% plot(l(:,1));
[T,S,D] = svds(A,50);
Aux = S*D';

% passo 4
[idx,centros] = kmeans(Aux',3);

A1 = find(idx == 1);
numel(A1);

A2 = find(idx == 2);
numel(A2);

A3 = find(idx == 3);
numel(A3);

% passo 5
calculateDist(centros','dist');
generateSolution(centros',3,'dist','result');
load result;
x = result(1,:);
y = result(2,:);
z = result(3,:);
plot3(x,y,z,'or', 'Color', 'b');
hold on;
plot3(x(1),y(1),z(1),'or', 'Color', 'r', "MarkerSize", numel(A1)/20, 'MarkerFaceColor','#d43d6a');
hold on;
plot3(x(2),y(2),z(2),'or', 'Color', 'r', "MarkerSize", numel(A2)/20, 'MarkerFaceColor','#d43d6a');
hold on;
plot3(x(3),y(3),z(3),'or', 'Color', 'r', "MarkerSize", numel(A3)/20, 'MarkerFaceColor','#d43d6a');
xlabel('X');
ylabel('Y');
zlabel('Z');
grid on;
