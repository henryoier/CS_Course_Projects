function p = gaussian(x, u, sigma)
%GAUSSIAN Summary of this function goes here
%   Detailed explanation goes here

p = (1/sqrt(det(2*pi*sigma)))*exp(-0.5*(x-u)'*inv(sigma)*(x-u));

end

