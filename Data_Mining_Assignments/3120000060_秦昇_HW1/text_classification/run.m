% ham_train contains the occurrences of each word in ham emails. 1-by-N vector
ham_train = csvread('ham_train.csv');
% spam_train contains the occurrences of each word in spam emails. 1-by-N vector
spam_train = csvread('spam_train.csv');
% N is the size of vocabulary.
N = size(ham_train, 2);
% There 9034 ham emails and 3372 spam emails in the training samples
num_ham_train = 9034;
num_spam_train = 3372;
% Do smoothing
x = [ham_train;spam_train] + 1;

% ham_test contains the occurences of each word in each ham test email. P-by-N vector, with P is number of ham test emails.
load ham_test.txt;
ham_test_tight = spconvert(ham_test);
ham_test = sparse(size(ham_test_tight, 1), size(ham_train, 2));
ham_test(:, 1:size(ham_test_tight, 2)) = ham_test_tight;
% spam_test contains the occurences of each word in each spam test email. Q-by-N vector, with Q is number of spam test emails.
load spam_test.txt;
spam_test_tight = spconvert(spam_test);
spam_test = sparse(size(spam_test_tight, 1), size(spam_train, 2));
spam_test(:, 1:size(spam_test_tight, 2)) = spam_test_tight;

% Your code HERE
%Implement a ham/spam email classifier, and calculate the accuracy of your classifier
P_ham = size(ham_test, 1);
Q_spam = size(spam_test, 1);
l = log10(likelihood(x));
r = l(2, :)-l(1, :);
[sr, index] = sort(r);
Top10 = index(N-9:N);
Top10
pr = log10([num_ham_train/(num_ham_train+num_spam_train);num_spam_train/(num_ham_train+num_spam_train)]);
mis_ham = 0;
for i=1:P_ham
    if (sum(ham_test(i,:).*l(1,:))+pr(1))<(sum(ham_test(i,:).*l(2,:))+pr(2));
        mis_ham = mis_ham + 1;
    end
end
mis_spam = 0;
for i=1:Q_spam
    if (sum(spam_test(i,:).*l(1,:))+pr(1))>(sum(ham_test(i,:).*l(2,:))+pr(2));
        mis_spam = mis_spam + 1;
    end
end
accuracy = (P_ham + Q_spam - mis_ham - mis_spam) / (P_ham + Q_spam) 
TP = Q_spam - mis_spam;
FP = mis_ham;
FN = mis_spam;
TN = P_ham - mis_ham;
[ TP, FP; FN, TN]
precision = TP/(TP + FP)
recall = TP/(FP + FN)