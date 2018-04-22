open Belt;

type action =
  | ChangeText(string)
  | ToggleTodo(TodoItem.todo)
  | AddNewTodo
  | CancelNewTodo
  | DeleteAll;

type state = {
  todos: list(TodoItem.todo),
  currentText: string,
};

let saveTodos = todos => Storage.saveTodos(todos);

let reducer = (action, state: state) =>
  switch (action) {
  | ChangeText(str) => ReasonReact.Update({...state, currentText: str})
  | ToggleTodo(todoToToggle) =>
    ReasonReact.UpdateWithSideEffects(
      {
        let todos =
          state.todos
          |> List.map(_, todo =>
               todo.id === todoToToggle.id ?
                 {...todo, completed: ! todo.completed} : todo
             );
        {...state, todos};
      },
      (self => saveTodos(self.state.todos)),
    )
  | AddNewTodo =>
    switch (String.trim(state.currentText)) {
    | "" => ReasonReact.NoUpdate
    | title =>
      ReasonReact.UpdateWithSideEffects(
        {
          let newTodo: TodoItem.todo = {
            id: Js.Date.(make() |> toISOString),
            title,
            completed: false,
          };
          let todos = [newTodo] @ state.todos;
          {todos, currentText: ""};
        },
        (self => saveTodos(self.state.todos)),
      )
    }
  | CancelNewTodo => ReasonReact.Update({...state, currentText: ""})
  | DeleteAll =>
    ReasonReact.UpdateWithSideEffects(
      {...state, todos: []},
      (self => saveTodos(self.state.todos)),
    )
  };

let initialState = () => {currentText: "", todos: Storage.loadTodos()};

let onInputChange = ({ReasonReact.send}, e) =>
  send(
    ChangeText(
      ReactDOMRe.domElementToObj(ReactEventRe.Form.target(e))##value,
    ),
  );

let onInputKeyDown = ({ReasonReact.send}, e) => {
  let key = ReactEventRe.Keyboard.key(e);
  switch (key) {
  | "Enter" =>
    e |> ReactEventRe.Keyboard.preventDefault;
    send(AddNewTodo);
  | "Escape" =>
    e |> ReactEventRe.Keyboard.preventDefault;
    send(CancelNewTodo);
  | _ => ()
  };
};

let onTodoToggle = ({ReasonReact.send}, todo: TodoItem.todo) =>
  send(ToggleTodo(todo));

let onRemoveAllClick = ({ReasonReact.send}, _e) => send(DeleteAll);

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  reducer,
  initialState,
  render: self =>
    <div>
      <input
        value=self.state.currentText
        onChange=(onInputChange(self))
        onKeyDown=(onInputKeyDown(self))
      />
      <TodoList
        todos=self.state.todos
        onToggle=(onTodoToggle(self))
        onRemoveAll=(onRemoveAllClick(self))
      />
    </div>,
};
