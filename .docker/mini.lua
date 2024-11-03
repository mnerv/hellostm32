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

-- Global options
vim.o.wildmenu = true    -- Command line completion mode
vim.o.wildmode = 'full'  -- Command line completion mode

-- Turn off line numbers in terminal mode
vim.api.nvim_command('autocmd TermOpen * setlocal nonu nornu nolist')
vim.api.nvim_command('autocmd TermEnter * setlocal nonu nornu nolist')

-- Detect file format
vim.o.fileformats = "unix,dos"

-- Basic Color
vim.api.nvim_set_hl(0, 'Whitespace', { fg = '#3a3a3a', ctermfg = 237 })

-- Keybinds

-- jk to escape
vim.keymap.set('i', 'jk', '<Esc>', {
  noremap = true,
  silent = true,
  desc = "Escape insert mode"
})

-- Escape from insert mode in terminal
vim.keymap.set('t', '<Esc>', '<C-\\><C-n>', {
  noremap = true,
  silent = true,
  desc = "Escape terminal insert mode"
})

-- Window navigation prefix
vim.keymap.set('n', '<space>w', '<C-w>', {
  noremap = true,
  silent = true,
  desc = "Window navigation"
})

-- Move current line up and down with alt+j and alt+k
vim.keymap.set('n', '<A-j>', ':m .+1<CR>==', {
  noremap = true,
  silent = true,
  desc = "Move current line down"
})
vim.keymap.set('n', '<A-k>', ':m .-2<CR>==', {
  noremap = true,
  silent = true,
  desc = "Move current line up"
})

-- Move highlighted lines up and down with alt+j and alt+k
vim.keymap.set('v', '<A-j>', ":m '>+1<CR>gv=gv", {
  noremap = true,
  silent = true,
  desc = "Move selected lines down"
})
vim.keymap.set('v', '<A-k>', ":m '<-2<CR>gv=gv", {
  noremap = true,
  silent = true,
  desc = "Move selected lines up"
})
