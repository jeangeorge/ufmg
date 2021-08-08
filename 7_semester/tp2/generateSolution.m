% Implemented by Leandro Soriano Marcolino. See readme for details;
% modified by Marcos Santos in 02/06/2010

function generateSolution(A, dim, distFile, outputFile)
    function [z,g] = E(D, y)
        z = 0;
        n = size(D, 1);
        
        for i = 1 : n - 1
            for j = i : n
                tmp = 0;
                for d = 1 : dim
                  tmp = tmp + (y(dim*i - (d - 1)) - y(dim*j - (d - 1)))^2;
                end
                z = z + (D(i, j) - tmp)^2;
            end
        end
        
        g = Eline(D, y);
    end


    function [y] = P(i, j, y)        
        tmp = y(dim*i-(dim-1):dim*i);
        y(dim*i-(dim-1):dim*i) = y(dim*j-(dim-1):dim*j);
        y(dim*j-(dim-1):dim*j) = tmp(1:dim);
    end

    function [z] = Eline(D, y)
        z = 0;
        n = size(D, 1);
        
        for i = 1 : n - 1
            for j = i : n
                z = z + 4*(D(i, j) - (y'*y - y'*P(i,j,y)))*(-y + P(i, j,y));
            end
        end
    end

    function main()
        Dist = load(distFile);
        Dist = Dist.D;

        % modificação para tratar os cossenos-----------------------------
        if isempty(A) ~= 1
            [T, S, D] = svds(A,dim);
            vectors = S*D';
            y = zeros(size(vectors,2)*dim,1);
            for m = 1 : dim : size(y,1)
                for n = 1 : dim
                    y(m + n - 1) = vectors(n,round((m+(dim-1))/dim));
                end
            end
        else 
            [T, S, D] = svds(Dist,dim);
            vectors = S*D';
            y = zeros(size(vectors,2)*dim,1);
            for m = 1 : dim : size(y,1)
                for n = 1 : dim
                    y(m + n - 1) = vectors(n,round((m+(dim-1))/dim));
                end
            end
        end
        %------------------------------------------------------------------
        r = fminunc(@(x)E(Dist,(x)),y,optimset('GradObj','on','TolFun',0.0001,'TolX',0.0001,'LargeScale','off'));
        
        result = zeros(dim, size(r, 1)/dim);

        for i = 1 : dim : size(r,1)
            for n = 1 : dim
                result(n, round((i + dim - 1)/dim)) = r(i + n - 1);
            end
        end
        
        save(outputFile, 'result');
    end

    main();
end