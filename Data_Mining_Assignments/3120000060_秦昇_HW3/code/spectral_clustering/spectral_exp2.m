load('TDT2_data', 'fea', 'gnd');
% YOUR CODE HERE

spectral_AC=0;
spectral_MIhat=0;
for testI=1:100
    W=constructW(fea);
    res = spectral(W,5);

    res = bestMap(gnd,res);
    %=============  evaluate AC: accuracy ==============
    spectral_AC = spectral_AC+length(find(gnd == res))/length(gnd);
    %=============  evaluate MIhat: nomalized mutual information =================s
    spectral_MIhat = spectral_MIhat+MutualInfo(gnd,res);
end;
average_spectral_AC=spectral_AC/100
average_spectral_MIhat=spectral_MIhat/100

% kmeans:
kmeans_AC=0;
kmeans_MIhat=0;
for testI=1:100
    res = litekmeans(fea,5);

    res = bestMap(gnd,res);
    %=============  evaluate AC: accuracy ==============
    kmeans_AC = kmeans_AC+length(find(gnd == res))/length(gnd);
    %=============  evaluate MIhat: nomalized mutual information =================
    kmeans_MIhat = kmeans_MIhat+MutualInfo(gnd,res);
end;
average_kmeans_AC=kmeans_AC/100
average_kmeans_MIhat=kmeans_MIhat/100
