-- SciCore project-local Neovim config.
-- Loaded via 'exrc' from the project root — run :trust once to authorize it.

-- Project root = directory containing this file.
local root = vim.fn.fnamemodify(debug.getinfo(1, "S").source:sub(2), ":h")

-- :make builds the whole project; CMake recompiles only what changed.
-- Global (not opt_local) so it applies to every buffer opened in this project.
vim.opt.makeprg = "cmake --build build"

-- ── Assembly view (<leader>a0 / a2 / a3) ──────────────────────────────────────
-- Compile the CURRENT .cpp with the LOCAL compiler (your GCC 16) to Intel-syntax
-- assembly at the chosen optimization level, shown in a vertical split. Uses your
-- real toolchain, headers and -march=native — authoritative for "what does my build
-- actually emit", unlike the remote godbolt service. The C++ standard comes from a
-- _NN filename suffix (hello42_20 -> C++20), defaulting to C++23.
--
-- Each level gets its own buffer name, so opening a0 then a2 leaves both splits up
-- for side-by-side comparison.
local function show_asm(opt)
  if vim.fn.expand("%:e") ~= "cpp" then
    vim.notify("Not a .cpp file", vim.log.levels.WARN)
    return
  end

  local file = vim.fn.expand("%:p")
  local stem = vim.fn.expand("%:t:r")
  local std = stem:match("_(%d%d)$") or "23"

  local cmd = {
    "g++", "-std=c++" .. std, "-" .. opt, "-march=native",
    "-S", "-masm=intel", "-fverbose-asm",
    "-I", vim.fn.expand("%:p:h"),       -- the file's own directory (same-dir headers)
    "-I", root .. "/external/mdspan",   -- vendored mdspan
    file, "-o", "-",
  }

  local out = vim.fn.systemlist(cmd)
  if vim.v.shell_error ~= 0 then
    vim.notify(table.concat(out, "\n"), vim.log.levels.ERROR)
    return
  end

  vim.cmd("vsplit")
  local buf = vim.api.nvim_create_buf(false, true)
  vim.api.nvim_win_set_buf(0, buf)
  vim.api.nvim_buf_set_lines(buf, 0, -1, false, out)
  vim.bo[buf].filetype = "asm"
  vim.bo[buf].buftype = "nofile"
  vim.bo[buf].bufhidden = "wipe"
  pcall(vim.api.nvim_buf_set_name, buf,
    ("asm://%s (c++%s -%s)"):format(stem, std, opt))
end

local function map_asm(bufnr)
  for _, opt in ipairs({ "O0", "O2", "O3" }) do
    vim.keymap.set("n", "<leader>a" .. opt:sub(2), function() show_asm(opt) end,
      { buffer = bufnr, desc = "Assembly -" .. opt .. " (local g++)" })
  end
end

-- Bind whenever a C++ buffer's filetype is set OR we enter one. Using both events
-- closes the startup race: when launched as `nvim file.cpp`, FileType can fire before
-- exrc sources this file, so BufEnter catches that already-open buffer too.
-- Pattern is '*' (FileType matches against the filetype string, not the filename,
-- so we guard on filetype inside the callback instead).
vim.api.nvim_create_autocmd({ "FileType", "BufEnter" }, {
  pattern = "*",
  callback = function(ev)
    if vim.bo[ev.buf].filetype == "cpp" then
      map_asm(ev.buf)
    end
  end,
})

-- And bind the current buffer immediately, in case it's already a loaded cpp file.
if vim.bo.filetype == "cpp" then
  map_asm(0)
end
