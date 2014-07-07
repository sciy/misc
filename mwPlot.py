# matplotlib.org/users/screenshots.html 
# https://github.com/olgabot/prettyplotlib/tree/master/tests

figure()
subplot(1,1,1)
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
