syntax on
set mouse=a
set smartindent
set shiftwidth=4
set autoindent
imap ( ()<ESC>i
imap { {}<ESC>i
set number
set ruler
let @/= ' \+$'
highlight DoubleSpace ctermbg=yellow
match DoubleSpace '  '
set directory=~/.vim/
