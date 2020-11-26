format-version := 0.0.0

environment:
	output :=
		'.fixed-header, .fixed-footer{'
		'	background: black;'
		'	color: white;'
		'}'

document:
	output :=
		'<link rel="stylesheet" href="document-environment.css">'
		header
		_children_
		footer
	styles:
		header:
			output :=
				'<div class="fixed-header">'
				'<p>' .. _text_block_ .. '</p>'
				'</div>'
				''
		footer:
			output :=
				'<div class="fixed-footer">'
				'<p>' .. _text_block_ .. '</p>'
				'</div>'
				''
		paragraph:
			output :=
				_text_block_
				''
		section:
			output :=
				'# ' .. section.title
				_children_
			default-child-style := paragraph
			styles:
				title:
					output :=
						_text_block_
				''
