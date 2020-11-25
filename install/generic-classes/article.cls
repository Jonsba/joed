format-version := 0.0.0

document:
	layout :=
		header
		_children_
		footer
	default-child-style := paragraph
	styles:
		header:
			type := text_block
		footer:
			type := text_block
		paragraph:
			type := text_block
		section:
			type := layout_block
			layout :=
				section.title
				_children_
			default-child-style := paragraph
			styles:
				title:
					type := text_block>title
