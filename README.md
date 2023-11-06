CPP note takings <br>
source: [LearnCpp Site](https://www.learncpp.com)

### What is needed to read .note files comfortably.
1) neovim (+0.8v)
2) vimwiki (plugin)
2) folke todo-comments (plugin)

Add this line of code to your neovim lua config:
```lua
vim.cmd [[ au BufRead,BufNewFile *.note setfiletype vimwiki ]]
```
