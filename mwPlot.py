figure()
subplot(2,1,1)
plot(...) #plot loglog semilogx; hist; semilogy; scatter ...
legend([..., ...], ['...', '...'])
xlim(0, ...)# set axis limits
ylim(0, ...)
subplot(2,1,2)
plot(...)
legend([..., ...], ['...', '...'])
xlim(0, ...)
ylim(0, ...)
xlabel('...')# make axis labels
ylabel('...')
title('Title $%d$ ...'%i)# give plot a title
savefig('...%05d.eps'%i)
