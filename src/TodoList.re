open Belt;

let component = ReasonReact.statelessComponent("TodoList");

let make = (~todos, ~onToggle, ~onRemoveAll, _children) => {
  ...component,
  render: _self =>
    switch (List.length(todos)) {
    | 0 => <p> (ReasonReact.stringToElement("Nie ma!")) </p>
    | _ =>
      let todoItems =
        todos
        |> List.map(_, (todo: TodoItem.todo) =>
             <li key=todo.id>
               <label>
                 <input
                   _type="checkbox"
                   checked=todo.completed
                   onChange=(_e => onToggle(todo))
                 />
                 (ReasonReact.stringToElement(todo.title))
               </label>
             </li>
           );
      let todoElements = ReasonReact.arrayToElement(List.toArray(todoItems));
      <div>
        <ul> todoElements </ul>
        <button
          onClick=(
            e => {
              ReactEventRe.Mouse.preventDefault(e);
              onRemoveAll(e);
            }
          )>
          (ReasonReact.stringToElement({j|Usuń wszystko|j}))
        </button>
      </div>;
    },
};
