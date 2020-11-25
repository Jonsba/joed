format-version := 0.0.0

environment:
	output :=
		'\\setupinteraction[state=start]'
		'\\placebookmarks[chapter,title,section,subsection][chapter,title,section][force=yes]'
		'\\setupwhitespace[big]'
		header
		footer

document:
	output :=
		'\\environment {document-environment}'
		'\\starttext'
		_children_
		'\\stoptext'
	styles:
		header:
			output :=
				'\\setupheadertexts[' .. _text_block_ .. ']'
		footer:
			output :=
				'\\setupfootertexts[' .. _text_block_ .. ']'
		paragraph:
			output :=
				'{\\par ' .. _text_block_ .. '}'
		section:
			output :=
				'\\startsection[title={' .. section.title .. '}]'
				_children_
				'\\stopsection'
			styles:
				title:
					output :=
						_text_block_
