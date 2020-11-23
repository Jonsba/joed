format-version := 0.0.0

environment:
	output :=
		'\\setupinteraction[state=start]'
		'\\placebookmarks[chapter,title,section,subsection][chapter,title,section][force=yes]'
		'\\setupwhitespace[big]'
		header
		footer

document-styles:
	output :=
		'\\environment {document-environment}'
		'\\starttext'
		_children_
		'\\stoptext'
	styles:
		header:
			output :=
				'\\setupheadertexts[' .. _text_content_ .. ']'
		footer:
			output :=
				'\\setupfootertexts[' .. _text_content_ .. ']'
		paragraph:
			output :=
				'{\\par ' .. _text_content_ .. '}'
		section:
			output :=
				'\\startsection[title={' .. section.title .. '}]'
				_children_
				'\\stopsection'
			styles:
				title:
					output :=
						_text_content_
