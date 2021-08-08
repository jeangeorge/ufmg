% Implemented by Leandro Soriano Marcolino. See readme for details.

function calculateDist(A, file)
    function [D] = distance(X)
        D = zeros(size(X,2));
        
        for i = 1 : size(X, 2)
            for j = i : size(X, 2)
                sum = 0;
                % for k = 1 : size(X,1)
                    %sum = sum + (X(k,i) - X(k,j))^2;
                 % end
                %%%%%D(i, j) = sqrt(soma); %optimization: the matrix will save dist^2
                aux = X(:, i) - X(:,j);
                sum = aux'*aux;
                D(i, j) = sum;
                D(j, i) = sum;
                
            end
           i 
        end        
    end

    D = distance(A);
    
    save(file,'D');
end