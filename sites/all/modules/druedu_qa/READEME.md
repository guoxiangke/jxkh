Druedu Q&A System
1.Summary
	Druedu Q&A System is an Q&A system like stackoverflow for Druedu(Next generation education solutions for schools based on Drupal).
	1.1 Requirement
		drupal 7.x
	1.2 Dependencies
			publication_date, statistics, token, views_ui, votingapi, rate, entity_token, rules, flag, views, filevault, filevault_field, druedu_qa_features
	1.3 More about druedu_qa_features.
		2 content types(Question&Answer) and fields.
		4 views.
		2 rules: rules_mark_question_resolved  and rules_mark_question_unresolved.
		1 flag: Accept.
		1 image_default_styles profile_small.

2.Implement
	2.1 Content types:
		We use two content types(Question&Answer) for questions and answers, and each has some fileds 
		1.1 Question
				Fileds:
					title: Question title.
					body: Long text and summary
					field_tags: Term reference.
					field_answers: Entity Reference from answers, one answers one record.
					field_computed_answers: total answers count of field field_answers.
					field_mark_question_resolved: Boolean,ture means the problem has best answer/resolved.
					field_attachments: FileVault file.
		1.2 Answer
				Fileds:
					title: Answer title. hide default and use auto_node_title.
					body: Long text and summary
					field_answer: Entity Reference to question.			
					field_attachments: FileVault file.

	2.2 Views
    	Questions : 
    		/questions: Page, all questions list of QA.
    		/questions/my-questions: Page, all questions list of current user.
    		/questions/unanswered: Page, all questions which have no 'Accept' answer.
    		/questions/tagged: Page, all questions have the same tag. must has query string: /?field_tags_tid=XXX
    	Questions tags: Block, show the Popular Tags of QA.
    	Related Questions: Block, seems no use.
    	Single question: 
    		/questions/[nid]: Page, the question page with answers.
3.Theme
	see tpls in templates folder.

4.Know issue
	filevault doesn't work,Developer can use your own attachment instead of filevault.



2013-02-17 14:37 by guo.