disp('TP1 Algoritmos para Bioinformática')

% a) Informar a matriz A no ambiente de prototipagem disponível
A = [0 0 0 1 0;...
    0 0 0 0 1;...
    0 0 0 0 1;...
    1 0 1 0 0;... %s no pdf ta 1 0 1 0 0 mas no video do professor ta 0 0 1 0 1
    1 0 0 0 0;...
    0 1 0 0 0 ;...
    1 0 1 1 0;...
    0 1 1 0 0;...
    0 0 1 1 1;...
    0 1 1 0 0];

% b) Proceder à decomposição por valores singulares da matriz A
[T, S, D] = svd(A);

% c) Verifique que A = T * S * D'. Dica: compute norm(A – T*S*D’, 2)
norma = norm(A - T*S*D', 2)

% d) Represente os documentos em um gráfico
Combinacoes = S*D';
x = Combinacoes(1,:);
y = Combinacoes(2,:);
plot(x, y, 'ko', 'markerfacecolor', 'r');
grid on;
hold on;
plot(0,0, 'sb');

% e) Informar a query e projetá-la no espaço reduzido, resolvendo o sistema de equações de m linhas por duas colunas
q = [0 0 0 0 0 0 0 1 1 1]';
T2 = T(:, 1:2);
qtil = T2'*q;

% % f) Representar a query no gráfico produzido
plot(qtil(1), qtil(2), 's', 'markerfacecolor', 'k');
p1 = [0 0];
for i = 1:5
    istr = num2str(i);
    text(x(i), y(i), ['  Doc ' istr]);
    p2 = [x(i) y(i)];
    dp = p2 -p1;
    quiver(p1(1),p1(2),dp(1),dp(2),0);
end
text(qtil(1), qtil(2), ['  Consulta']);
p2 = [qtil(1) qtil(2)];
dp = p2-p1;
quiver(p1(1),p1(2),dp(1),dp(2),0);
title('  TP1 - Algoritmos para Bioinformática');
xlabel('Uso do padrão 1 ');
ylabel('Uso do padrão 2');

% calculo dos cossenos
cossenos = 1 - pdist2([x; y]', qtil', 'cosine');