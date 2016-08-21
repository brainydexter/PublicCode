using UnityEngine;

using System;
using System.Collections.Generic;

public interface IEventType
{
}

public interface IEventAggregator {
    void Update();
    void Publish(IEventType e);
	void Register<T>(Action<IEventType> subscriber) where T : IEventType;
	void UnRegister<T>(Action<IEventType> subscriber) where T : IEventType;
}

public class EventAggregator : IEventAggregator
{
	protected Dictionary<Type, Action<IEventType> > collection;

    protected Queue<IEventType> eventQueue;

    public EventAggregator(){
		collection = new Dictionary<Type, Action<IEventType>> ();

        eventQueue = new Queue<IEventType> ();

		Debug.Log ("[EventAggregator]: Created event aggregator");
    }

	public void OnDestroy() {
		collection.Clear (); collection = null;
		eventQueue.Clear (); eventQueue = null;
		Debug.Log ("[EventAggregator]: Destroyed event aggregator");
	}

    /// <summary>
    /// Processes all the events in the eventQueue
    /// </summary>
    public void Update(){

		while (this.eventQueue.Count > 0) {
			IEventType evnt = this.eventQueue.Dequeue ();

			Action<IEventType> subscribers;

			if (collection.TryGetValue (evnt.GetType (), out subscribers)) {
				Debug.Log ("[EventAggregator]: Processing event: " + evnt);
				subscribers.Invoke (evnt);
			} else {
				Debug.LogError ("[EventAggregator]: No subscriber for eventtype: " + evnt.GetType ());
			}

			evnt = null; // marking it for GC
		}
    }

    /// <summary>
    /// Queues the event to be published in the next update
    /// </summary>
    /// <param name="e">E.</param>
    public void Publish (IEventType e)
    {
        eventQueue.Enqueue (e);
    }

	/// <summary>
	/// Register the specified subscriber for the eventType
	/// </summary>
	/// <param name="subscriber">Subscriber.</param>
	/// <typeparam name="T">The 1st type parameter.</typeparam>
	public void Register<T>(Action<IEventType> subscriber) where T : IEventType
	{
		Type type = typeof(T);
		Debug.Log ("[EventAggregator]: Registering subscriber for eventType: " + type);

		if (!collection.ContainsKey (type))
			collection.Add(type, subscriber);
		else
			collection [type] += subscriber;
	}

	public void UnRegister<T>(Action<IEventType> subscriber) where T : IEventType
	{
		Type type = typeof(T);
		Debug.Log ("[EventAggregator]: UnRegistering subscriber for eventType: " + type);

		if (collection.ContainsKey (type)) {
			collection [type] -= subscriber;
		} else {
			Debug.LogError ("[EventAggregator]: " + subscriber + " not found in collection for event: " + type);
		}
	}
}

public class ValidWord : IEventType 
{
    public ValidWord (String word, Vector3 posn)
    {
        this.word = word;
        this.wordPosition = posn;
    }
    public string word;
    public Vector3 wordPosition;

    public Type getType()
    {
        return typeof(ValidWord);
    }
}

public class InvalidWord : IEventType 
{
    public InvalidWord (Vector3 posn)
    {
        this.wordPosition = posn;
    }
    public Vector3 wordPosition;

    public Type getType()
    {
        return typeof(InvalidWord);
    }
}

