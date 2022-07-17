set mouse=a

set number
set fillchars=fold:\ ,vert:\│,eob:\ ,msgsep:‾
set nowrap
set showbreak=+++
set textwidth=100
"set showmatch
set visualbell

set hlsearch
set smartcase
set ignorecase
set incsearch

set autoindent
set tabstop=4
set shiftwidth=4
set cindent shiftwidth=4
set softtabstop=4
set noexpandtab


set undolevels=1000
set backspace=indent,eol,start

nnoremap <C-J> <C-W><C-J>
nnoremap <C-K> <C-W><C-K>
nnoremap <C-L> <C-W><C-L>
nnoremap <C-H> <C-W><C-H>

" clipboard
set clipboard=unnamedplus
nnoremap <y> "+y<CR>
nnoremap <p> "+p<CR>

" syntax and colors
colorscheme base16-tomorrow-night
set background=dark
set termguicolors

" lightline
let g:lightline = {
     \ 'colorscheme': 'Tomorrow_Night',
     \ }
set noshowmode

" toggle bg color
function! ToggleColor()
    ToggleBG
    execute 'source' globpath(&rtp,  "autoload/lightline/colorscheme/one.vim")
    call lightline#init()
    call lightline#colorscheme()
    call lightline#update()
endfunction

" nerdtree config
let NERDTreeMinimalUI=1
map <C-n> :NERDTreeToggle<CR>
autocmd bufenter * if (winnr("$") == 1 && exists("b:NERDTree") && b:NERDTree.isTabTree()) | q | endif
let g:NERDTreeDirArrowExpandable = ''
let g:NERDTreeDirArrowCollapsible = ''
