format-version := 0.0.0

environment:
	output :=
		'.fixed-header, .fixed-footer{'
		'	background: black;'
		'	color: white;'
		'}'
		'p {'
		'	margin-top: 2em;'
		'	margin-bottom: 2em;'
		'}'

document-styles:
	output :=
		'<link rel="stylesheet" href="document-environment.css">'
		header
		_children_
		footer
	styles:
		header:
			output :=
				'<div class="fixed-header">'
				'<p>' .. _text_content_ .. '</p>'
				'</div>'
				''
		footer:
			output :=
				'<div class="fixed-footer">'
				'<p>' .. _text_content_ .. '</p>'
				'</div>'
				''
		paragraph:
			output :=
				_text_content_
				''
		section:
			output :=
				'# ' .. section.title
				_children_
			default-child-style := paragraph
			styles:
				title:
					output :=
						_text_content_
				''
