# matplotlib.org/users/screenshots.html 
# https://github.com/olgabot/prettyplotlib/tree/master/tests

figure()
subplot(1,1,1) # subplot(3,1,1); subplot(3,1,2); subplot(3,1,3); for 3 subfigures (up and down).
plot(...) #plot loglog semilogx; hist; semilogy; scatter ...
legend([..., ...], ['...', '...'])
xlim(0, ...)# set axis limits
ylim(0, ...)
xticks([...])
yticks([...])
xlabel('...')# make axis labels
ylabel('...')
title('Title $%d$ ...'%i)# give plot a title
savefig('...%05d.eps'%i)
