format-version := 0.0.0

environment:
	output :=
		'body{'
		'	padding-top: 60px;'
		'	padding-bottom: 80px;'
		'}'
		'.fixed-header, .fixed-footer{'
		'	width: 100%;'
		'	position: fixed;'
		'	background: #333;'
		'	padding: 10px 0;'
		'	color: #fff;'
		'}'
		'.fixed-header{'
		'	top: 0;'
		'}'
		'.fixed-footer{'
		'	bottom: 0;'
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
