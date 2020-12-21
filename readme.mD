<h1>Codam Coding College Project: minishell</h1>
<p>minishell in collaboration with YUSHUA@github</p>
<p><b>Project description:</b><br>
A simplified shell program that follows the rules of bash.</p>
<p><b>Functionalities</b>:<br>
- Shows a prompt when waiting for a new command<br>
- Search and launch the right executable (based on the PATH variable or the relative or absolute path), like in bash.<br>
- Shell built-ins:<br>
&nbsp;&nbsp;&nbsp;&nbsp;- <code>echo</code> with option '<code>-n</code>'<br>
&nbsp;&nbsp;&nbsp;&nbsp;- <code>cd</code> with only a relative or absolute path<br>
&nbsp;&nbsp;&nbsp;&nbsp;- <code>pwd</code> without any options<br>
&nbsp;&nbsp;&nbsp;&nbsp;- <code>export</code> without any options<br>
&nbsp;&nbsp;&nbsp;&nbsp;- <code>unset</code> without any options<br>
&nbsp;&nbsp;&nbsp;&nbsp;- <code>env</code> without any options and any arguments<br>
&nbsp;&nbsp;&nbsp;&nbsp;- <code>exit</code> without any options.<br>
- <code>;</code> in the command should separate commands like in bash<br>
- <code>'</code> and <code>"</code> should work like in bash except for multiline commands.<br>
- Redirections <code>&gt;</code> <code>&gt;&gt;</code> <code>&lt;</code> works like in bash except for file descriptor aggregation.<br>
- Pipes <code>|</code> work like in bash<br>
- environment variables (<code>$</code> followed by characters) work like in bash<br>
- <code>$?</code> works like in bash<br>
- <code>ctrl-C</code>, <code>ctrl-D</code>, <code>ctrl-\</code> have the same results as in bash.</p>
<h2>Using the project</h2>
<p>Clone the project with git clone:<br>
<code>git clone [repo_link] [folder_name]</code></p>
<p>Create the executable:<br>
<code>make</code></p>
<p>Run the executable:<br>
<code>./minishell</code></p>
<p>A prompt will show up that will allow you to use minishell as your current shell.</p>
