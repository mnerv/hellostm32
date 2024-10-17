-- Neovim configuration file for Docker development

-- White space characters configuration
vim.opt.listchars = 'tab:›  ,trail:~,extends:>,precedes:<,space:∙'
vim.opt.list = true

vim.opt.mouse = 'a'    -- Enable mouse support

-- Line numbers configuration
vim.opt.number = true          -- Line numbers
vim.opt.relativenumber = true  -- Relative line numbers

-- Tab configuration
vim.opt.expandtab   = true   -- Use spaces instead of tabs
vim.opt.smarttab    = true   -- Use shiftwidth when inserting shiftwidth number of spaces
vim.opt.linebreak   = true   -- Break lines at convenient points
vim.opt.wrap        = false  -- Wrap lines
vim.opt.smartindent = true   -- Insert indents automatically
vim.opt.shiftwidth  = 4      -- Number of spaces to use for autoindent
vim.opt.tabstop     = 4      -- Number of spaces that a <Tab> in the file counts for
vim.opt.smartcase   = true   -- Override 'ignorecase' if the search pattern contains upper case characters

-- Search configuration
vim.opt.completeopt = {'menu', 'menuone', 'noinsert', 'noselect'}
vim.opt.wildmode    = {'list', 'longest'} -- Command-line completion mode
vim.opt.splitbelow  = true                -- Put new windows below current
vim.opt.splitright  = true                -- Put new windows right of current

vim.opt.hidden = true   -- Enable Background buffers

vim.opt.shortmess = vim.opt.shortmess + 'c'

-- jk to escape
vim.api.nvim_set_keymap('i', 'jk', '<Esc>', { noremap = true })

-- Global options
vim.o.wildmenu = true    -- Command line completion mode
vim.o.wildmode = 'full'  -- Command line completion mode

-- Turn off line numbers in terminal mode
vim.api.nvim_command('autocmd TermOpen * setlocal nonu nornu nolist')
vim.api.nvim_command('autocmd TermEnter * setlocal nonu nornu nolist')
-- Escape from insert mode in terminal
vim.api.nvim_set_keymap('t', '<Esc>', '<C-\\><C-n>', { noremap = true })

vim.api.nvim_set_keymap('n', '<space>w', '<C-w>', { noremap = true })

vim.api.nvim_set_keymap('n', '<A-j>', ':m .+1<CR>==', { noremap = true})
vim.api.nvim_set_keymap('n', '<A-k>', ':m .-2<CR>==', { noremap = true})

