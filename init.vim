set visualbell
set ttimeoutlen=5
syntax on
au BufNewFile,BufRead shader.*,*.glsl setf glsl

call plug#begin()
Plug 'hrsh7th/nvim-cmp'
Plug 'hrsh7th/cmp-nvim-lsp'
Plug 'mhartington/oceanic-next'
call plug#end()

colorschem OceanicNext
set background=dark
set rnu nu
set hlsearch
set smartcase
set ignorecase
set tabstop=4 softtabstop=4
set shiftwidth=4
set expandtab
set ruler
set autochdir
set signcolumn=yes

set colorcolumn=80
highlight ColorColumn guifg=#bdae93 guibg=#3c3836

set updatetime=250
hi Search cterm=bold ctermfg=128 ctermbg=green
autocmd CursorHold * :exec 'match Search /\V\<' . substitute(expand('<cword>'), '/', '\\/', "g") . '\>/'


highlight DiffAdd    cterm=bold ctermfg=10 ctermbg=17 gui=none guifg=bg guibg=Red
highlight DiffDelete cterm=bold ctermfg=10 ctermbg=17 gui=none guifg=bg guibg=Red
highlight DiffChange cterm=bold ctermfg=10 ctermbg=17 gui=none guifg=bg guibg=Red
highlight DiffText   cterm=bold ctermfg=10 ctermbg=88 gui=none guifg=bg guibg=Red

let mapleader=' '

nnoremap <leader>s :syntax sync fromstart<CR>

nnoremap <leader>h :wincmd h<CR>
nnoremap <leader>j :wincmd j<CR>
nnoremap <leader>k :wincmd k<CR>
nnoremap <leader>l :wincmd l<CR>

let target = '//:main'
nnoremap <leader>t :exec '!cat input \|  bazel run '.target<CR>

"let ttarget = '//:main'
"nnoremap <leader>t :exec '!bazel test --test_output=all '.ttarget<CR>

nnoremap <leader>q :exec ':!luacheck --no-color main.lua; lua main.lua'<CR>

fun! TrimWhitespace()
    let l:save = winsaveview()
    keeppatterns %s/\s\+$//e
    call winrestview(l:save)
endfun

autocmd BufWritePre * :call TrimWhitespace()
set mouse=

" LSP setup
lua <<EOF
    local cmp = require'cmp'
    cmp.setup {
        sources = {
            { name = 'nvim_lsp' }
        },
        mapping = {
            ['<CR>'] = cmp.mapping.confirm({select = true}),
            ['<Tab>'] = cmp.mapping.select_next_item({ behavior = cmp.SelectBehavior.Insert}),
        }
    }
    local capabilities = require('cmp_nvim_lsp').default_capabilities()

    vim.api.nvim_create_autocmd({"FileType"}, {
        pattern = {"cpp"},
        callback = function(event)
        vim.lsp.start({
        name = 'clangd',
        capabilities = capabilities,
        cmd = {'clangd'},
        root_dir = vim.fs.dirname(vim.fs.find({'MODULE.bazel', 'WORKSPACE'}, { upward = true })[0]),
        })
        end
    })

    vim.api.nvim_create_autocmd('LspAttach', {
        callback = function(args)
        vim.keymap.set('n', '<leader>gd', vim.lsp.buf.definition, { silent = true })
        vim.keymap.set('n', '<leader>gr', vim.lsp.buf.references, { silent = true })
        vim.keymap.set('n', '<leader>rn', vim.lsp.buf.rename, { silent = true })
        vim.keymap.set('n', '<leader>f', vim.lsp.buf.format, { silent = true })
        vim.keymap.set('n', '[d', vim.diagnostic.goto_next, { silent = true })
        vim.keymap.set('n', ']d', vim.diagnostic.goto_prev, { silent = true })
        end,
    })
EOF
