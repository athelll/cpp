CPP note takings <br>
source: [LearnCpp Site](https://www.learncpp.com)

[[What is needed to read .note files]]
1) neovim
2) vimwiki (plugin)

Add this line of code to your neovim lua config:
```lua
vim.cmd [[ au BufRead,BufNewFile *.note setfiletype vimwiki ]]
```
