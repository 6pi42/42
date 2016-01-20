(defun ffr-insert-parentheses ()
	(interactive)
	(insert "()")
	(backward-char 1))
(defun ffr-insert-braces ()
	(interactive)
	(insert "{}")
	(backward-char 1))

(column-number-mode 1)

(setq default-directory "~/.emacs.d" )

(add-hook 'c-mode-common-hook '(lambda ()
								(local-set-key (kbd "RET") 'newline-and-indent)))
(add-hook 'c-mode-common-hook (lambda ()
								(local-set-key "(" 'ffr-insert-parentheses)))
(add-hook 'c-mode-common-hook (lambda ()
								(local-set-key "{" 'ffr-insert-braces)))
