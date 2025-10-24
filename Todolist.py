#A todo list is the desire
# List to store tasks
tasks = []

# Main loop
while True:
    # Display the menu
    print("\nTo-Do List Menu:")
    print("1. Add a Task")
    print("2. View Tasks")
    print("3. Remove a Task")
    print("4. Exit")

    #user input
    choice = input("Choose an Option (1-4): ")
    #define each task
    if choice == "1":
        task = input("enter the task: ")
        tasks.append(task)
        print(f'"{task}" has been added to the list')

    elif choice == "2": #view the tasks
        if tasks: #checks if there any tasks
            print('\nYour tasks:"')
        for i, task in enumerate(tasks, start=1):
            print(f"{i}. {task}") 
        else:
            print("Your todo list is empty.")
    elif choice == "3": #remove a task #this will error if there is a selected task that does not exist
        if tasks: #checks if there are any tasks
            try:
                remv = int(input("enter the task to be removed (one at a time)"))
                if remv <= len(tasks) and remv >= 1: # can only remove what exists
                    tasks.pop(remv-1) # it starts at zero
                else: 
                    print("This Task number is not on the list")
            except ValueError: #handles non possible error beyond invalid numbers
                print("Invalid input. Enter a valid number")
        else:
            print("Task list is empty...nothing to remove.")
        
    elif choice == "4":
        print("Good-Bye!")
        break
    else:
        print("invalid choice, select 1-4")


