##### aimldl > computing_environments > git > udacity > README.md


### Commit Message Style

#### Summary: [Udacity Git Commit Message Style Guide](https://udacity.github.io/git-styleguide/)
##### Message Structure
> type: subject
>
> body
>
> footer

Three distinct parts separated by a blank line: the title, an optional body and an optional footer.

##### type
> feat: a new feature
fix: a bug fix
docs: changes to documentation
style: formatting, missing semi colons, etc; no code change
refactor: refactoring production code
test: adding tests, refactoring test; no production code change
chore: updating build tasks, package manager configs, etc; no production code change


##### subject
* No greater than ***50 characters***
* Begin with a capital letter
* Do not end with a period
* Use an imperative tone
  * Example
    * GOOD: Change README
    * BAD:  Changed README
    * BAD:  Changes README

##### body (optional)
* The length of each line is no more than ***72 characters***
  * --> Wrap it to 72 characters if necessary.
* Use the body to explain the ***what*** and ***why*** of a commit, ***not the how***.
* Further paragraphs come after blank lines.
  > Paragraph 1
  >
  > Paragraph 2
  >
  > (More paragrahs)
  >
  > Paragraph n
* Bullet points are okay.
  * Typically a hyphen or asterisk is used for the bullet,
  * preceded by a single space, with blank lines in between.
##### footer (optional)
is used to reference issue tracker IDs. For example,
> Resolves: #123
See also: #456, #789


(EOF)
